#ifndef VANADIUM_THEMESELECTOR_H
#define VANADIUM_THEMESELECTOR_H

class ThemeSelector
{
public:
    enum class Theme
    {
        Light = 0,
        Classic,
        Dark,
        Reddish,
        Grayish,
        Blender,
        Source,
    };



private:
    static Theme currentTheme;

    static void applyThemeFromEnum(Theme theme);

public:
    static void reapply();
    static Theme getCurrent();
    static void setTheme(Theme theme);
    static void styleColorsLight();
    static void styleColorsDark();
    static void styleColorsClassic();
    static void styleColorsReddish();
    static void styleColorsGrayish();
    static void styleColorsBlender();
    static void styleColorsSource();

};

#endif //VANADIUM_THEMESELECTOR_H
