#include "CheckerPlayer.h"


CheckerPlayer::CheckerPlayer(Color color) : m_color(color) {}

Color CheckerPlayer::color() {
    return m_color;
}
