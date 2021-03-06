#include "DefaultKeyCodes.h"
#include "../../core/Assert.h"

namespace Vanadium
{

namespace Mouse
{

std::string toString(Mouse::KeyCode arg)
{
    switch(arg)
    {
        case Mouse::KeyCode::Unknown: return "Unknown";
        case Mouse::KeyCode::Left: return "Left";
        case Mouse::KeyCode::Middle: return "Middle";
        case Mouse::KeyCode::Right: return "Right";
        case Mouse::KeyCode::X1: return "X1";
        case Mouse::KeyCode::X2: return "X2";
    }
    VAN_ENGINE_ASSERT(false, "Unknown Mouse::KeyCode!");
    return "Unknown";
}
Mouse::KeyCode fromString(const std::string &arg)
{
    unsigned long hash = hashString(arg);

    switch(hash)
    {
        case "Left"_hash: return Mouse::KeyCode::Left;
        case "Middle"_hash: return Mouse::KeyCode::Middle;
        case "Right"_hash: return Mouse::KeyCode::Right;
        case "X1"_hash: return Mouse::KeyCode::X1;
        case "X2"_hash: return Mouse::KeyCode::X2;
        default: return Mouse::KeyCode::Unknown;
    }
}

}

namespace Keyboard
{

std::string toString(KeyCode arg)
{
    switch(arg)
    {
        case Keyboard::KeyCode::Unknown: return "Unknown";
        case Keyboard::KeyCode::A: return "A";
        case Keyboard::KeyCode::B: return "B";
        case Keyboard::KeyCode::C: return "C";
        case Keyboard::KeyCode::D: return "D";
        case Keyboard::KeyCode::E: return "E";
        case Keyboard::KeyCode::F: return "F";
        case Keyboard::KeyCode::G: return "G";
        case Keyboard::KeyCode::H: return "H";
        case Keyboard::KeyCode::I: return "I";
        case Keyboard::KeyCode::J: return "J";
        case Keyboard::KeyCode::K: return "K";
        case Keyboard::KeyCode::L: return "L";
        case Keyboard::KeyCode::M: return "M";
        case Keyboard::KeyCode::N: return "N";
        case Keyboard::KeyCode::O: return "O";
        case Keyboard::KeyCode::P: return "P";
        case Keyboard::KeyCode::Q: return "Q";
        case Keyboard::KeyCode::R: return "R";
        case Keyboard::KeyCode::S: return "S";
        case Keyboard::KeyCode::T: return "T";
        case Keyboard::KeyCode::U: return "U";
        case Keyboard::KeyCode::V: return "V";
        case Keyboard::KeyCode::W: return "W";
        case Keyboard::KeyCode::X: return "X";
        case Keyboard::KeyCode::Y: return "Y";
        case Keyboard::KeyCode::Z: return "Z";
        case Keyboard::KeyCode::Num_1: return "Num_1";
        case Keyboard::KeyCode::Num_2: return "Num_2";
        case Keyboard::KeyCode::Num_3: return "Num_3";
        case Keyboard::KeyCode::Num_4: return "Num_4";
        case Keyboard::KeyCode::Num_5: return "Num_5";
        case Keyboard::KeyCode::Num_6: return "Num_6";
        case Keyboard::KeyCode::Num_7: return "Num_7";
        case Keyboard::KeyCode::Num_8: return "Num_8";
        case Keyboard::KeyCode::Num_9: return "Num_9";
        case Keyboard::KeyCode::Num_10: return "Num_10";
        case Keyboard::KeyCode::Return: return "Return";
        case Keyboard::KeyCode::Escape: return "Escape";
        case Keyboard::KeyCode::Backspace: return "Backspace";
        case Keyboard::KeyCode::Tab: return "Tab";
        case Keyboard::KeyCode::Space: return "Space";
        case Keyboard::KeyCode::Minus: return "Minus";
        case Keyboard::KeyCode::Equals: return "Equals";
        case Keyboard::KeyCode::LeftBracket: return "LeftBracket";
        case Keyboard::KeyCode::RightBracket: return "RightBracket";
        case Keyboard::KeyCode::Backslash: return "Backslash";
        case Keyboard::KeyCode::Semicolon: return "Semicolon";
        case Keyboard::KeyCode::Apostrophe: return "Apostrophe";
        case Keyboard::KeyCode::Grave: return "Grave";
        case Keyboard::KeyCode::Comma: return "Comma";
        case Keyboard::KeyCode::Period: return "Period";
        case Keyboard::KeyCode::Slash: return "Slash";
        case Keyboard::KeyCode::Capslock: return "Capslock";
        case Keyboard::KeyCode::F1: return "F1";
        case Keyboard::KeyCode::F2: return "F2";
        case Keyboard::KeyCode::F3: return "F3";
        case Keyboard::KeyCode::F4: return "F4";
        case Keyboard::KeyCode::F5: return "F5";
        case Keyboard::KeyCode::F6: return "F6";
        case Keyboard::KeyCode::F7: return "F7";
        case Keyboard::KeyCode::F8: return "F8";
        case Keyboard::KeyCode::F9: return "F9";
        case Keyboard::KeyCode::F10: return "F10";
        case Keyboard::KeyCode::F11: return "F11";
        case Keyboard::KeyCode::F12: return "F12";
        case Keyboard::KeyCode::PrintScreen: return "PrintScreen";
        case Keyboard::KeyCode::ScrollLock: return "ScrollLock";
        case Keyboard::KeyCode::Pause: return "Pause";
        case Keyboard::KeyCode::Insert: return "Insert";
        case Keyboard::KeyCode::Home: return "Home";
        case Keyboard::KeyCode::PageUp: return "PageUp";
        case Keyboard::KeyCode::Delete: return "Delete";
        case Keyboard::KeyCode::End: return "End";
        case Keyboard::KeyCode::PageDown: return "PageDown";
        case Keyboard::KeyCode::Right: return "Right";
        case Keyboard::KeyCode::Left: return "Left";
        case Keyboard::KeyCode::Down: return "Down";
        case Keyboard::KeyCode::Up: return "Up";
        case Keyboard::KeyCode::NumLock: return "NumLock";
        case Keyboard::KeyCode::KPDivide: return "KPDivide";
        case Keyboard::KeyCode::KPMultiply: return "KPMultiply";
        case Keyboard::KeyCode::KP_Minus: return "KP_Minus";
        case Keyboard::KeyCode::KP_Plus: return "KP_Plus";
        case Keyboard::KeyCode::KP_Enter: return "KP_Enter";
        case Keyboard::KeyCode::KP_1: return "KP_1";
        case Keyboard::KeyCode::KP_2: return "KP_2";
        case Keyboard::KeyCode::KP_3: return "KP_3";
        case Keyboard::KeyCode::KP_4: return "KP_4";
        case Keyboard::KeyCode::KP_5: return "KP_5";
        case Keyboard::KeyCode::KP_6: return "KP_6";
        case Keyboard::KeyCode::KP_7: return "KP_7";
        case Keyboard::KeyCode::KP_8: return "KP_8";
        case Keyboard::KeyCode::KP_9: return "KP_9";
        case Keyboard::KeyCode::KP_0: return "KP_0";
        case Keyboard::KeyCode::KP_Period: return "KP_Period";
        case Keyboard::KeyCode::KP_Equals: return "KP_Equals";
        case Keyboard::KeyCode::F13: return "F13";
        case Keyboard::KeyCode::F14: return "F14";
        case Keyboard::KeyCode::F15: return "F15";
        case Keyboard::KeyCode::F16: return "F16";
        case Keyboard::KeyCode::F17: return "F17";
        case Keyboard::KeyCode::F18: return "F18";
        case Keyboard::KeyCode::F19: return "F19";
        case Keyboard::KeyCode::F20: return "F20";
        case Keyboard::KeyCode::F21: return "F21";
        case Keyboard::KeyCode::F22: return "F22";
        case Keyboard::KeyCode::F23: return "F23";
        case Keyboard::KeyCode::F24: return "F24";
        case Keyboard::KeyCode::Execute: return "Execute";
        case Keyboard::KeyCode::Help: return "Help";
        case Keyboard::KeyCode::Menu: return "Menu";
        case Keyboard::KeyCode::Select: return "Select";
        case Keyboard::KeyCode::Stop: return "Stop";
        case Keyboard::KeyCode::Redo: return "Redo";
        case Keyboard::KeyCode::Undo: return "Undo";
        case Keyboard::KeyCode::Cut: return "Cut";
        case Keyboard::KeyCode::Copy: return "Copy";
        case Keyboard::KeyCode::Paste: return "Paste";
        case Keyboard::KeyCode::Find: return "Find";
        case Keyboard::KeyCode::Mute: return "Mute";
        case Keyboard::KeyCode::VolumeUp: return "VolumeUp";
        case Keyboard::KeyCode::VolumeDown: return "VolumeDown";
        case Keyboard::KeyCode::KP_Comma: return "KP_Comma";
        case Keyboard::KeyCode::LCtrl: return "LCtrl";
        case Keyboard::KeyCode::LShift: return "LShift";
        case Keyboard::KeyCode::LAlt: return "LAlt";
        case Keyboard::KeyCode::LMeta: return "LMeta";
        case Keyboard::KeyCode::RCtrl: return "RCtrl";
        case Keyboard::KeyCode::RShift: return "RShift";
        case Keyboard::KeyCode::RAlt: return "RAlt";
        case Keyboard::KeyCode::RMeta: return "RMeta";
    }
    VAN_ENGINE_ASSERT(false, "Unknown Keyboard::KeyCode!");
    return "God help us all.";
}

Keyboard::KeyCode fromString(const std::string &arg)
{
    unsigned long hash = hashString(arg);

    switch(hash)
    {
        case "A"_hash: return Keyboard::KeyCode::A;
        case "B"_hash: return Keyboard::KeyCode::B;
        case "C"_hash: return Keyboard::KeyCode::C;
        case "D"_hash: return Keyboard::KeyCode::D;
        case "E"_hash: return Keyboard::KeyCode::E;
        case "F"_hash: return Keyboard::KeyCode::F;
        case "G"_hash: return Keyboard::KeyCode::G;
        case "H"_hash: return Keyboard::KeyCode::H;
        case "I"_hash: return Keyboard::KeyCode::I;
        case "J"_hash: return Keyboard::KeyCode::J;
        case "K"_hash: return Keyboard::KeyCode::K;
        case "L"_hash: return Keyboard::KeyCode::L;
        case "M"_hash: return Keyboard::KeyCode::M;
        case "N"_hash: return Keyboard::KeyCode::N;
        case "O"_hash: return Keyboard::KeyCode::O;
        case "P"_hash: return Keyboard::KeyCode::P;
        case "Q"_hash: return Keyboard::KeyCode::Q;
        case "R"_hash: return Keyboard::KeyCode::R;
        case "S"_hash: return Keyboard::KeyCode::S;
        case "T"_hash: return Keyboard::KeyCode::T;
        case "U"_hash: return Keyboard::KeyCode::U;
        case "V"_hash: return Keyboard::KeyCode::V;
        case "W"_hash: return Keyboard::KeyCode::W;
        case "X"_hash: return Keyboard::KeyCode::X;
        case "Y"_hash: return Keyboard::KeyCode::Y;
        case "Z"_hash: return Keyboard::KeyCode::Z;
        case "Num_1"_hash: return Keyboard::KeyCode::Num_1;
        case "Num_2"_hash: return Keyboard::KeyCode::Num_2;
        case "Num_3"_hash: return Keyboard::KeyCode::Num_3;
        case "Num_4"_hash: return Keyboard::KeyCode::Num_4;
        case "Num_5"_hash: return Keyboard::KeyCode::Num_5;
        case "Num_6"_hash: return Keyboard::KeyCode::Num_6;
        case "Num_7"_hash: return Keyboard::KeyCode::Num_7;
        case "Num_8"_hash: return Keyboard::KeyCode::Num_8;
        case "Num_9"_hash: return Keyboard::KeyCode::Num_9;
        case "Num_10"_hash: return Keyboard::KeyCode::Num_10;
        case "Return"_hash: return Keyboard::KeyCode::Return;
        case "Escape"_hash: return Keyboard::KeyCode::Escape;
        case "Backspace"_hash: return Keyboard::KeyCode::Backspace;
        case "Tab"_hash: return Keyboard::KeyCode::Tab;
        case "Space"_hash: return Keyboard::KeyCode::Space;
        case "Minus"_hash: return Keyboard::KeyCode::Minus;
        case "Equals"_hash: return Keyboard::KeyCode::Equals;
        case "LeftBracket"_hash: return Keyboard::KeyCode::LeftBracket;
        case "RightBracket"_hash: return Keyboard::KeyCode::RightBracket;
        case "Backslash"_hash: return Keyboard::KeyCode::Backslash;
        case "Semicolon"_hash: return Keyboard::KeyCode::Semicolon;
        case "Apostrophe"_hash: return Keyboard::KeyCode::Apostrophe;
        case "Grave"_hash: return Keyboard::KeyCode::Grave;
        case "Comma"_hash: return Keyboard::KeyCode::Comma;
        case "Period"_hash: return Keyboard::KeyCode::Period;
        case "Slash"_hash: return Keyboard::KeyCode::Slash;
        case "Capslock"_hash: return Keyboard::KeyCode::Capslock;
        case "F1"_hash: return Keyboard::KeyCode::F1;
        case "F2"_hash: return Keyboard::KeyCode::F2;
        case "F3"_hash: return Keyboard::KeyCode::F3;
        case "F4"_hash: return Keyboard::KeyCode::F4;
        case "F5"_hash: return Keyboard::KeyCode::F5;
        case "F6"_hash: return Keyboard::KeyCode::F6;
        case "F7"_hash: return Keyboard::KeyCode::F7;
        case "F8"_hash: return Keyboard::KeyCode::F8;
        case "F9"_hash: return Keyboard::KeyCode::F9;
        case "F10"_hash: return Keyboard::KeyCode::F10;
        case "F11"_hash: return Keyboard::KeyCode::F11;
        case "F12"_hash: return Keyboard::KeyCode::F12;
        case "PrintScreen"_hash: return Keyboard::KeyCode::PrintScreen;
        case "ScrollLock"_hash: return Keyboard::KeyCode::ScrollLock;
        case "Pause"_hash: return Keyboard::KeyCode::Pause;
        case "Insert"_hash: return Keyboard::KeyCode::Insert;
        case "Home"_hash: return Keyboard::KeyCode::Home;
        case "PageUp"_hash: return Keyboard::KeyCode::PageUp;
        case "Delete"_hash: return Keyboard::KeyCode::Delete;
        case "End"_hash: return Keyboard::KeyCode::End;
        case "PageDown"_hash: return Keyboard::KeyCode::PageDown;
        case "Right"_hash: return Keyboard::KeyCode::Right;
        case "Left"_hash: return Keyboard::KeyCode::Left;
        case "Down"_hash: return Keyboard::KeyCode::Down;
        case "Up"_hash: return Keyboard::KeyCode::Up;
        case "NumLock"_hash: return Keyboard::KeyCode::NumLock;
        case "KPDivide"_hash: return Keyboard::KeyCode::KPDivide;
        case "KPMultiply"_hash: return Keyboard::KeyCode::KPMultiply;
        case "KP_Minus"_hash: return Keyboard::KeyCode::KP_Minus;
        case "KP_Plus"_hash: return Keyboard::KeyCode::KP_Plus;
        case "KP_Enter"_hash: return Keyboard::KeyCode::KP_Enter;
        case "KP_1"_hash: return Keyboard::KeyCode::KP_1;
        case "KP_2"_hash: return Keyboard::KeyCode::KP_2;
        case "KP_3"_hash: return Keyboard::KeyCode::KP_3;
        case "KP_4"_hash: return Keyboard::KeyCode::KP_4;
        case "KP_5"_hash: return Keyboard::KeyCode::KP_5;
        case "KP_6"_hash: return Keyboard::KeyCode::KP_6;
        case "KP_7"_hash: return Keyboard::KeyCode::KP_7;
        case "KP_8"_hash: return Keyboard::KeyCode::KP_8;
        case "KP_9"_hash: return Keyboard::KeyCode::KP_9;
        case "KP_0"_hash: return Keyboard::KeyCode::KP_0;
        case "KP_Period"_hash: return Keyboard::KeyCode::KP_Period;
        case "KP_Equals"_hash: return Keyboard::KeyCode::KP_Equals;
        case "F13"_hash: return Keyboard::KeyCode::F13;
        case "F14"_hash: return Keyboard::KeyCode::F14;
        case "F15"_hash: return Keyboard::KeyCode::F15;
        case "F16"_hash: return Keyboard::KeyCode::F16;
        case "F17"_hash: return Keyboard::KeyCode::F17;
        case "F18"_hash: return Keyboard::KeyCode::F18;
        case "F19"_hash: return Keyboard::KeyCode::F19;
        case "F20"_hash: return Keyboard::KeyCode::F20;
        case "F21"_hash: return Keyboard::KeyCode::F21;
        case "F22"_hash: return Keyboard::KeyCode::F22;
        case "F23"_hash: return Keyboard::KeyCode::F23;
        case "F24"_hash: return Keyboard::KeyCode::F24;
        case "Execute"_hash: return Keyboard::KeyCode::Execute;
        case "Help"_hash: return Keyboard::KeyCode::Help;
        case "Menu"_hash: return Keyboard::KeyCode::Menu;
        case "Select"_hash: return Keyboard::KeyCode::Select;
        case "Stop"_hash: return Keyboard::KeyCode::Stop;
        case "Redo"_hash: return Keyboard::KeyCode::Redo;
        case "Undo"_hash: return Keyboard::KeyCode::Undo;
        case "Cut"_hash: return Keyboard::KeyCode::Cut;
        case "Copy"_hash: return Keyboard::KeyCode::Copy;
        case "Paste"_hash: return Keyboard::KeyCode::Paste;
        case "Find"_hash: return Keyboard::KeyCode::Find;
        case "Mute"_hash: return Keyboard::KeyCode::Mute;
        case "VolumeUp"_hash: return Keyboard::KeyCode::VolumeUp;
        case "VolumeDown"_hash: return Keyboard::KeyCode::VolumeDown;
        case "KP_Comma"_hash: return Keyboard::KeyCode::KP_Comma;
        case "LCtrl"_hash: return Keyboard::KeyCode::LCtrl;
        case "LShift"_hash: return Keyboard::KeyCode::LShift;
        case "LAlt"_hash: return Keyboard::KeyCode::LAlt;
        case "LMeta"_hash: return Keyboard::KeyCode::LMeta;
        case "RCtrl"_hash: return Keyboard::KeyCode::RCtrl;
        case "RShift"_hash: return Keyboard::KeyCode::RShift;
        case "RAlt"_hash: return Keyboard::KeyCode::RAlt;
        case "RMeta"_hash: return Keyboard::KeyCode::RMeta;
        default: return Keyboard::KeyCode::Unknown;
    }
}

}

}