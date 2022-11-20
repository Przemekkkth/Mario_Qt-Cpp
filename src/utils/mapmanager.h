#ifndef MAPMANAGER_H
#define MAPMANAGER_H
#include <QRgb>
#include <QImage>
#include <QPixmap>
#include "global.h"

class GameScene;
class MapManager
{
public:
    static const QMap<QRgb, GLOBAL::CELL_TYPE> colorToCellMap;
    MapManager();

    int getMapSketchHeight() const;
    int getMapSketchWidth() const;
    int getMapWidth() const;

    void drawMap(const bool drawBackground, const bool underground, const unsigned view_x, GameScene& scene);
    void drawBackground(int cameraX, GameScene& scene);
    void setMapCell(const int x, const int y, const GLOBAL::CELL_TYPE& cell);
    GLOBAL::CELL_TYPE mapCell(int x, int y) const;
    void setMapSize(const int new_size);
    void updateMapSketch(const int current_level);

    QRgb getMapSketchPixel(const int x, const int y) const;
    void convertFromSketch(int currentLevel);
private:
    QImage m_mapSketch;

    QPixmap m_cellSprite;

    QPixmap m_mapTexture;

    GLOBAL::Map m_map;
    static const QMap<QRgb, QPoint> colorToPointOfSpriteMap;
    static const QMap<GLOBAL::CELL_TYPE, QPoint> cellToPointOfSpriteMap;
    static const QList<GLOBAL::CELL_TYPE> animatedCells;
};
#endif // MAPMANAGER_H
