//=========================================================
//  MusE
//  Linux Music Editor
//    $Id: canvas.h,v 1.3.2.8 2009/02/02 21:38:01 terminator356 Exp $
//  (C) Copyright 1999 Werner Schweer (ws@seh.de)
//  Additions, modifications (C) Copyright 2011 Tim E. Real (terminator356 on users DOT sourceforge DOT net)
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; version 2 of
//  the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//
//=========================================================

#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "citem.h"
#include "view.h"
#include "tools.h"
#include "undo.h"

#include <QWheelEvent>
#include <QMouseEvent>
#include <QKeyEvent>

#include <vector>

class QMenu;

namespace MusEGui {

//---------------------------------------------------------
//   Canvas
//---------------------------------------------------------

class Canvas : public View {
      Q_OBJECT
      int canvasTools;
      QTimer *scrollTimer;
      
      bool doScroll;
      int scrollSpeed;

      QPoint ev_pos;
      bool canScrollLeft;
      bool canScrollRight;
      bool canScrollUp;
      bool canScrollDown;

   protected:
      enum DragMode {
            DRAG_OFF, DRAG_NEW,
            DRAG_MOVE_START, DRAG_MOVE,
            DRAG_COPY_START, DRAG_COPY,
            DRAG_CLONE_START, DRAG_CLONE,
            DRAGX_MOVE, DRAGY_MOVE,
            DRAGX_COPY, DRAGY_COPY,
            DRAGX_CLONE, DRAGY_CLONE,
            DRAG_DELETE,
            DRAG_RESIZE, DRAG_LASSO_START, DRAG_LASSO,
            };

      enum DragType {
            MOVE_MOVE, MOVE_COPY, MOVE_CLONE
            };

      enum HScrollDir {
            HSCROLL_NONE, HSCROLL_LEFT, HSCROLL_RIGHT
            };
      enum VScrollDir {
            VSCROLL_NONE, VSCROLL_UP, VSCROLL_DOWN
            };
      
      //CItemList items;
      CItemList moving;
      CItem* curItem;

      // Items layers. Used during painting. Exact usage depends on subclass. They are free to add as many layers as needed.
      // The derived classes are asked to sort the 'items' list into the itemLayers for drawing.
      // The draw() method will call sortLayerItem() for each item in each list in each layer. 
      // Layer 0 is bottom layer of items (first drawn). (These are not allocated CItems, simply pointers.)
      CItemLayers items;  
      std::vector<std::vector<CItem*> > itemLayers;  

      DragMode drag;
      QRect lasso;
      QPoint start;
      Tool _tool;
      unsigned pos[3];
      
      HScrollDir hscrollDir;
      VScrollDir vscrollDir;
      int button;
      Qt::KeyboardModifiers keyState;
      QMenu* itemPopupMenu;
      QMenu* canvasPopupMenu;

      void setCursor();
      virtual void viewKeyPressEvent(QKeyEvent* event);
      virtual void viewMousePressEvent(QMouseEvent* event);
      virtual void viewMouseMoveEvent(QMouseEvent*);
      virtual void viewMouseReleaseEvent(QMouseEvent*);
      virtual void draw(QPainter&, const QRect&);
      virtual void wheelEvent(QWheelEvent* e);

      virtual bool mousePress(QMouseEvent*) { return true; }
      virtual void keyPress(QKeyEvent*);
      virtual void mouseMove(QMouseEvent* event) = 0;
      virtual void mouseRelease(const QPoint&) {}
      virtual void drawCanvas(QPainter&, const QRect&) = 0;
      virtual void drawTopItem(QPainter& p, const QRect& rect) = 0;

      // Subclasses can override with custom drawing sequences. For example automation requires drawing the layer 
      //  once as connected lines, then drawing the layer again as vertex 'boxes' on TOP OF the lines.
      // The default simply calls drawItem().
      virtual void drawItemLayer(QPainter& p, const QRect& r, int layer); 
      //virtual void drawItem(QPainter&, const CItem*, const QRect&) = 0;
      virtual void drawItem(QPainter&, const CItem*, const QRect&, int layer) = 0;  // Layer can be -1 for moving.
      virtual void drawMoving(QPainter&, const CItem*, const QRect&) = 0;
      virtual void updateSelection() = 0;
      virtual QPoint raster(const QPoint&) const = 0;
      virtual int y2pitch(int) const = 0; //CDW
      virtual int pitch2y(int) const = 0; //CDW
      // The derived classes are asked to sort the 'items' list into 'itemLayers' for drawing.
      //virtual void sortLayerItem(CItem* item) = 0;

      virtual CItem* newItem(const QPoint&, int state) = 0;
      virtual void resizeItem(CItem*, bool noSnap=false, bool ctrl=false) = 0;
      virtual void newItem(CItem*, bool noSnap=false) = 0;
      virtual bool deleteItem(CItem*) = 0;
      //virtual void deleteItem(const QPoint&);
      virtual void deleteItemAtPoint(const QPoint&) = 0;

      int getCurrentDrag();

      /*!
         \brief Virtual member

         Implementing class is responsible for creating a popup to be shown when the user rightclicks an item on the Canvas
         \param item The canvas item that is rightclicked
         \return A QPopupMenu*
         */
      virtual QMenu* genItemPopup(CItem* /*item*/) { return 0; }

      /*!
         \brief Pure virtual member

         Implementing class is responsible for creating a popup to be shown when the user rightclicks an empty region of the canvas
         \return A QPopupMenu*
         */
      QMenu* genCanvasPopup();

      /*!
         \brief Virtual member

         This is the function called when the user has selected an option in the popupmenu generated by genItemPopup()
         \param item the canvas item the whole thing is about
         \param n Command type
         \param pt I think this is the position of the pointer when right mouse button was pressed
         */
      virtual void itemPopup(CItem* /*item */, int /*n*/, const QPoint& /*pt*/) {}
      void canvasPopup(int);

      virtual void startDrag(CItem*, bool) {}

      // selection
      virtual void deselectAll();
      virtual void selectItem(CItem* e, bool);
      virtual void selectItemRow(bool) { }

      // moving
      void startMoving(const QPoint&, DragType);
      
      void moveItems(const QPoint&, int dir, bool rasterize = true);
      virtual void endMoveItems(const QPoint&, DragType, int dir) = 0;

      // Default is to select all items in all layers. Override in subclasses for specific behaviour.
      virtual void selectLasso(bool toggle);

      virtual void itemPressed(const CItem*) {}
      virtual void itemReleased(const CItem*, const QPoint&) {}
      virtual void itemMoved(const CItem*, const QPoint&) {}
      virtual void curItemChanged() {}
      virtual void curPartChanged() {}     // TODO Try to eliminate this base method - minimum base will then be in EventCanvas
      // virtual void curPartChanged() { emit curPartHasChanged(curPart); } // REMOVE Tim.

   public slots:
      void setTool(int t);
      void setPos(int, unsigned, bool adjustScrollbar);
      void scrollTimerDone(void);
      void redirectedWheelEvent(QWheelEvent*);

   signals:
      void followEvent(int);
      void toolChanged(int);
      void verticalScroll(unsigned);
      void horizontalScroll(unsigned);
      void horizontalScrollNoLimit(unsigned);
      void horizontalZoomIn();
      void horizontalZoomOut();
      //void curPartHasChanged(MusECore::Part*);  // REMOVE Tim.
      
   public:
      Canvas(QWidget* parent, int sx, int sy, const char* name = 0);
      virtual ~Canvas();
      //bool isSingleSelection();
      bool isSingleSelection(int layer = -1);
      //int selectionSize();
      int selectionSize(int layer = -1);
      Tool tool() const { return _tool; }
      //MusECore::Part* part() const { return curPart; }
      //void setCurrentPart(MusECore::Part*); 
      void setCanvasTools(int n) { canvasTools = n; }
      };

} // namespace MusEGui

#endif

