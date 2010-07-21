//=========================================================
//  MusE
//  Linux Music Editor
//    $Id: piano.cpp,v 1.3 2004/05/31 11:48:55 lunar_shuttle Exp $
//  (C) Copyright 1999 Werner Schweer (ws@seh.de)
//=========================================================

#include <qpainter.h>

#include <stdio.h>

#include "piano.h"

static const char *oct_xpm[] = {
// w h colors
      "40 91 2 1",
      ". c #c0c0c0",
      "# c #000000",
      //           x
      "####################################### ",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#", // 10
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#", //------------------------
      "#######################................#",
      "########################...............#",
      "########################...............#",
      "####################################### ",     // 7
      "########################...............#",
      "########################...............#",
      "#######################................#", //------------------------
      ".......................................#",
      ".......................................#",
      ".......................................#",     // 6
      ".......................................#",
      ".......................................#",
      ".......................................#", //------------------------
      "#######################................#",
      "########################...............#",
      "########################...............#",     // 7
      "####################################### ",
      "########################...............#",
      "########################...............#",
      "#######################................#", //------------------------
      ".......................................#",
      ".......................................#",
      ".......................................#",    // 6
      ".......................................#",
      ".......................................#",
      ".......................................#", //------------------------
      "#######################................#",
      "########################...............#",
      "########################...............#",    // 7
      "####################################### ",
      "########################...............#",
      "########################...............#",
      "#######################................#", //------------------------
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",    // 10
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      "####################################### ", //----------------------
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",    // 9
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#", //------------------------
      "#######################................#",
      "########################...............#",
      "########################...............#",
      "####################################### ",   // 7
      "########################...............#",
      "########################...............#",
      "#######################................#", //------------------------
      ".......................................#",
      ".......................................#",
      ".......................................#",     // 6
      ".......................................#",
      ".......................................#",
      ".......................................#", //--------------------------
      "#######################................#",
      "########################...............#",
      "########################...............#",     // 7
      "####################################### ",
      "########################...............#",
      "########################...............#",
      "#######################................#", //------------------------
      ".......................................#",
      "..........................###..........#",
      ".........................#...#.........#",
      ".........................#.............#",
      ".........................#.............#",
      ".........................#...#.........#",     // 10
      "..........................###..........#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
    };

static const char *mk1_xpmC1[] = {
      "40 10 2 1",
      ". c #c0c0c0",
      "# c #000000",
      ".......................................#",
      "..........................###.....#....#",
      ".........................#...#...##....#",
      ".........................#........#....#",
      ".........................#........#....#",
      ".........................#...#....#....#",     // 10
      "..........................###....###...#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      };
static const char *mk1_xpmC2[] = {
      "40 10 2 1",
      ". c #c0c0c0",
      "# c #000000",
      ".......................................#",
      "..........................###....##....#",
      ".........................#...#..#..#...#",
      ".........................#........#....#",
      ".........................#.......#.....#",
      ".........................#...#..#......#",     // 10
      "..........................###...####...#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      };
static const char *mk1_xpmC3[] = {
      "40 10 2 1",
      ". c #c0c0c0",
      "# c #000000",
      ".......................................#",
      "..........................###....##....#",
      ".........................#...#..#..#...#",
      ".........................#........#....#",
      ".........................#.........#...#",
      ".........................#...#..#..#...#",     // 10
      "..........................###....##....#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      };
static const char *mk1_xpmC4[] = {
      "40 10 2 1",
      ". c #c0c0c0",
      "# c #000000",
      ".......................................#",
      "..........................###...#..#...#",
      ".........................#...#..#..#...#",
      ".........................#......####...#",
      ".........................#.........#...#",
      ".........................#...#.....#...#",     // 10
      "..........................###......#...#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      };
static const char *mk1_xpmC5[] = {
      "40 10 2 1",
      ". c #c0c0c0",
      "# c #000000",
      ".......................................#",
      "..........................###...####...#",
      ".........................#...#..#......#",
      ".........................#......###....#",
      ".........................#.........#...#",
      ".........................#...#.....#...#",     // 10
      "..........................###...###....#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      };

static const char *mk1_xpmC6[] = {
      "40 10 2 1",
      ". c #c0c0c0",
      "# c #000000",
      ".......................................#",
      "..........................###....###...#",
      ".........................#...#..#......#",
      ".........................#......###....#",
      ".........................#......#..#...#",
      ".........................#...#..#..#...#",     // 10
      "..........................###...###....#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      };

static const char *mk1_xpmC7[] = {
      "40 10 2 1",
      ". c #c0c0c0",
      "# c #000000",
      ".......................................#",
      "..........................###...####...#",
      ".........................#...#.....#...#",
      ".........................#........#....#",
      ".........................#.......#.....#",
      ".........................#...#..#......#",     // 10
      "..........................###...#......#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      };
static const char *mk1_xpmC8[] = {
      "40 10 2 1",
      ". c #c0c0c0",
      "# c #000000",
      ".......................................#",
      "..........................###....##....#",
      ".........................#...#..#..#....#",
      ".........................#.......##....#",
      ".........................#......#..#...#",
      ".........................#...#..#..#...#",     // 10
      "..........................###....##....#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      };

static const char *mk1_xpm[] = {
      "40 13 2 1",
      ". c #ff0000",
      "# c none",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      "#######################................#",
      "########################...............#",
      "########################...............#",
      "####################################### ",
      };

static const char *mk2_xpm[] = {
      "40 13 2 1",
      ". c #ff0000",
      "# c none",
      "########################...............#",
      "########################...............#",
      "#######################................#", //------------------------
      ".......................................#",
      ".......................................#",
      ".......................................#",     // 6
      ".......................................#",
      ".......................................#",
      ".......................................#", //--------------------------
      "#######################................#",
      "########################...............#",
      "########################...............#",     // 7
      "####################################### ",
      };

static const char *mk3_xpm[] = {
      "40 13 2 1",
      ". c #ff0000",
      "# c none",
      "########################...............#",
      "########################...............#",
      "#######################................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      ".......................................#",
      "########################################",
      };

static const char *mk4_xpm[] = {
      "40 13 2 1",
      "# c #ff0000",
      ". c none",
      "........................................",
      "........................................",
      "........................................",
      "#######################.................",
      "########################................",
      "########################................",
      "########################................",
      "########################................",
      "########################................",
      "#######################.................",
      "........................................",
      "........................................",
      "........................................",
      };
/*
      0   1   2  3  4  5  6  7  8  9  10
      c-2 c-1 C0 C1 C2 C3 C4 C5 C6 C7 C8 - G8

      Grid �ber Oktave:

           +------------+ ------------------------------
       11  |            |
           |         h  |         7
           +------+     |
       10  |  a#  +-----+ ..............................
           +------+  a  |
        9  |            |         6
           +------+     |
        8  |  g#  +-----+ ..............................
           +------+  g  |
        7  |            |         5
           +------+     |
        6  |  f#  +-----+ ..............................
           +------+  f  |
        5  |            |         4
           |            |
           +------------+ ------------------------------
        4  |            |
           |         e  |         3
           +------+     |
        3  |  d#  +-----+ ..............................
           +------+  d  |
        2  |            |         2
           +------+     |
        1  |  c#  +-----+ ..............................
           +------+  c  |
           |            |         1
        0  |            |
           +------------+ ------------------------------
 */

//---------------------------------------------------------
//   Piano
//---------------------------------------------------------

Piano::Piano(QWidget* parent, int ymag)
   : View(parent, 1, ymag)
      {
      setMouseTracking(true);
      curPitch = -1;
      octave = new QPixmap(oct_xpm);
      c_keys[0] = new QPixmap(mk1_xpmC8);
      c_keys[1] = new QPixmap(mk1_xpmC7);
      c_keys[2] = new QPixmap(mk1_xpmC6);
      c_keys[3] = new QPixmap(mk1_xpmC5);
      c_keys[4] = new QPixmap(mk1_xpmC4);
      c_keys[5] = new QPixmap(mk1_xpmC3);
      c_keys[6] = new QPixmap(mk1_xpmC2);
      c_keys[7] = new QPixmap(mk1_xpmC1);

      mk1 = new QPixmap(mk1_xpm);
      mk2 = new QPixmap(mk2_xpm);
      mk3 = new QPixmap(mk3_xpm);
      mk4 = new QPixmap(mk4_xpm);
      keyDown = -1;
      button = NoButton;
      }

//---------------------------------------------------------
//   draw
//---------------------------------------------------------

void Piano::draw(QPainter& p, const QRect& r)
      {
      QPoint offset(0, KH*2);
      p.drawTiledPixmap(r, *octave, r.topLeft()+offset);

      // draw C notes
      for (int drawKey = 0; drawKey < 8;drawKey++) {
        int octaveSize=91;

        int drawY = octaveSize * drawKey + 81 - KH*2;
        if (drawY > r.y() && drawY < r.y() + r.height()) {
          //printf("drawing c %d at %d r.y %d r.x %d\n",drawKey, drawY, r.y(), r.x());
          p.drawPixmap(0,drawY,*c_keys[drawKey]);
        }
      }
      //p.drawTiledPixmap(r, *c1, r.topLeft()+offset + coffset);
      //printf("drawText KH %d %d, x %d y %d\n",KH, curPitch, r.x(), r.y());
      //p.drawText(r,Qt::AlignAuto,"A");
      if (curPitch == -1)
            return;
      int y = pitch2y(curPitch);
      QPixmap* pm;
      switch(curPitch % 12) {
            case 0:
            case 5:
                  pm = mk3;
                  break;
            case 2:
            case 7:
            case 9:
                  pm = mk2;
                  break;
            case 4:
            case 11:
                  pm = mk1;
                  break;
            default:
                  pm = mk4;
                  break;
            }
      p.drawPixmap(0, y, *pm);
      }

//---------------------------------------------------------
//   pitch2y
//---------------------------------------------------------

int Piano::pitch2y(int pitch) const
      {
      int tt[] = {
            12, 19, 25, 32, 38, 51, 58, 64, 71, 77, 84, 90
            };
      int y = (75 * KH) - (tt[pitch%12] + (7 * KH) * (pitch/12));
      if (y < 0)
            y = 0;
      return y;
      }

//---------------------------------------------------------
//   y2pitch
//---------------------------------------------------------

int Piano::y2pitch(int y) const
      {
      const int total = (10 * 7 + 5) * KH;       // 75 Ganztonschritte
      y = total - y;
      int oct = (y / (7 * KH)) * 12;
      char kt[] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 1,
            2, 2, 2, 2, 2, 2,
            3, 3, 3, 3, 3, 3, 3,
            4, 4, 4, 4, 4, 4, 4, 4, 4,
            5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
            6, 6, 6, 6, 6, 6, 6,
            7, 7, 7, 7, 7, 7,
            8, 8, 8, 8, 8, 8, 8,
            9, 9, 9, 9, 9, 9,
            10, 10, 10, 10, 10, 10, 10,
            11, 11, 11, 11, 11, 11, 11, 11, 11, 11
            };
      return kt[y % 91] + oct;
      }

//---------------------------------------------------------
//   leaveEvent
//---------------------------------------------------------

void Piano::leaveEvent(QEvent*)
      {
      if (keyDown != -1) {
            emit keyReleased(keyDown, shift);
            keyDown = -1;
            }
      emit pitchChanged(-1);
      setPitch(-1);
      }

//---------------------------------------------------------
//   setPitch
//---------------------------------------------------------

void Piano::setPitch(int pitch)
      {
      if (curPitch == pitch)
            return;
      curPitch = pitch;
      redraw();
      }

//---------------------------------------------------------
//   viewMouseMoveEvent
//---------------------------------------------------------

void Piano::viewMouseMoveEvent(QMouseEvent* event)
      {
      int pitch = y2pitch(event->y());
      emit pitchChanged(pitch);
      setPitch(pitch);

      if (button != NoButton) {
            int nk = y2pitch(event->y());
            if (nk < 0 || nk > 127)
                  nk = -1;
            if (nk != keyDown) {
                  if (keyDown != -1) {
                        emit keyReleased(keyDown, shift);
                        }
                  keyDown = nk;
                  if (keyDown != -1) {
                        int velocity = event->x()*127/40;
                        //emit keyPressed(keyDown, shift);
                        emit keyPressed(keyDown, velocity>127 ? 127 : velocity, shift);
                        }
                  }
            }
      }

//---------------------------------------------------------
//   viewMousePressEvent
//---------------------------------------------------------

void Piano::viewMousePressEvent(QMouseEvent* event)
      {
      button = event->button();
      shift  = event->state() & ShiftButton;
      if (keyDown != -1) {
            emit keyReleased(keyDown, shift);
            keyDown = -1;
            }
      keyDown = y2pitch(event->y());
      if (keyDown < 0 || keyDown > 127) {
            keyDown = -1;
            }
      else {
            int velocity = event->x()*127/40;
            emit keyPressed(keyDown, velocity>127 ? 127 : velocity, shift); //emit keyPressed(keyDown, shift);
            }
      }

//---------------------------------------------------------
//   viewMouseReleaseEvent
//---------------------------------------------------------

void Piano::viewMouseReleaseEvent(QMouseEvent* event)
      {
      button = NoButton;
      shift = event->state() & ShiftButton;
      if (keyDown != -1) {
            emit keyReleased(keyDown, shift);
            keyDown = -1;
            }
      }

