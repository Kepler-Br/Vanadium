#include <bgfx_shader.sh>

uniform vec4 u_resolution;
uniform vec4 u_auraColor;
uniform mat4 u_inversedProjectionView;
uniform vec4 u_cameraPosition;
uniform vec4 u_fractalParameter;
uniform vec4 u_iterations;
uniform vec4 u_bailout;

vec3 screenToWorld(vec4 fragCoord, in vec4 resolution,
                   in mat4 inversedProjectionView) {
  // NORMALISED DEVICE SPACE
  float x = 2.0f * fragCoord.x / resolution.x - 1.0f;
  float y = 2.0f * fragCoord.y / resolution.y - 1.0f;

  // HOMOGENEOUS SPACE
  vec4 screenPos = vec4(x, -y, -1.0f, 1.0f);

  vec4 worldPos = screenPos * inversedProjectionView;
  return normalize(vec3(worldPos));
}

// https://www.iquilezles.org/www/articles/mandelbulb/mandelbulb.htm
vec2 mandelbulb(vec3 position, in vec4 fractalParameter) {
  int iterations = int(u_iterations.x);
  float bailout = u_bailout.x;
  float power = 6. - 4. * cos(fractalParameter.x / 16.);

  vec3 trap = vec3(0, 0, 0);
  float minTrap = 1e10;

  vec3 z = position;
  float dr = 1.0;
  float r = 0.0;
  for (int i = 0; i < iterations; i++) {
    r = length(z);
    if (r > bailout) break;

    minTrap = min(minTrap, z.z);

    // convert to polar coordinates
    float theta = acos(z.z / r);
    float phi = atan(z.y / z.x);
    dr = pow(r, power - 1.0) * power * dr + 1.0;

    // scale and rotate the point
    float zr = pow(r, power);
    theta = theta * power;
    phi = phi * power;

    // convert back to cartesian coordinates
    z = zr * vec3(cos(theta) * cos(phi), cos(theta) * sin(phi), sin(theta));
    z += position;
  }
  return vec2(0.5 * log(r) * r / dr, minTrap);
}

float boxDistance(vec3 currentMarchingLocation, vec3 position, vec3 size) {
  vec3 offset = abs(currentMarchingLocation) - size;
  return length(max(offset, 0.0f)) +
         min(max(offset.x, max(offset.y, offset.z)), 0.0f);
}

float sphereDistance(vec3 currentMarchingLocation, vec3 position,
                     float radius) {
  return (length(currentMarchingLocation - position) - radius);
}

vec2 getDistance(vec3 currentMarchingLocation, in vec4 fractalParameter) {
  float sphereDistance =
      sphereDistance(currentMarchingLocation, vec3(0.0f, 0.0f, 0.0f), 0.01f);
  vec2 mandelbulb = mandelbulb(currentMarchingLocation, fractalParameter);
  if (mandelbulb.x > sphereDistance)
    return vec2(sphereDistance, 0.0f);
  else
    return mandelbulb;
}

vec3 rayMarch(vec3 rayOrigin, vec3 rayDirection, in vec4 fractalParameter) {
  float distanceFromOrigin = 0.0f;

  const int maxSteps = 100;
  const float maxDistance = 10.0f;
  const float minDistanceToSurface = 0.001f;

  int steps = 0;
  for (; steps < maxSteps; steps++) {
    vec3 currentMarchingLocation =
        rayOrigin + rayDirection * distanceFromOrigin;
    vec2 distanceToScene =
        getDistance(currentMarchingLocation, fractalParameter);
    distanceFromOrigin += distanceToScene.x;
    if (distanceToScene.x < minDistanceToSurface ||
        distanceFromOrigin > maxDistance)
      return vec3(distanceFromOrigin, steps, distanceToScene.y);
  }
  return vec3(0.0f);
}

vec3 getNormal(vec3 location, in vec4 fractalParameter) {
  const float epsilon = 0.001;
  float centerDistance = getDistance(location, fractalParameter).x;
  float xDistance =
      getDistance(location + vec3(epsilon, 0, 0), fractalParameter).x;
  float yDistance =
      getDistance(location + vec3(0, epsilon, 0), fractalParameter).x;
  float zDistance =
      getDistance(location + vec3(0, 0, epsilon), fractalParameter).x;
  vec3 normal =
      (vec3(xDistance, yDistance, zDistance) - centerDistance) / epsilon;
  return normalize(normal);
}

// https://iquilezles.org/www/articles/palettes/palettes.htm
vec3 pal(float t, vec3 a, vec3 b, vec3 c, vec3 d) {
  return a + b * cos(6.28318 * (c * t + d));
}

void main() {
  vec3 rayDirection =
      screenToWorld(gl_FragCoord, u_resolution, u_inversedProjectionView);
  vec3 distance =
      rayMarch(u_cameraPosition.xyz, rayDirection, u_fractalParameter);
  vec3 normal = getNormal(rayDirection * distance.x + u_cameraPosition.xyz,
                          u_fractalParameter);
  //  float trap = fract(distance.z*.5 + .5);
  distance = max(distance, 10.0f) / 10.0f;
  vec3 col = vec3(0.0f);
  //  col = (col + vec3(distance.y/100.0f, 0.0f, distance.y/200.0f))/2.0f;
  col = col + distance.yyy * u_auraColor.rgb;
  gl_FragColor = vec4(col, 1.0f);
}