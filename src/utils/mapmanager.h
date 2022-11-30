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
    static const QMap<GLOBAL::CELL_TYPE, QPoint> cellToPointOfSpriteMap;
    static const QMap<QRgb, QString> colorToEnemy;
    MapManager();

    int getMapSketchHeight() const;
    int getMapSketchWidth() const;
    int getMapWidth() const;

    void drawBackground(int cameraX, GameScene& scene);
    void drawForeground(int cameraX, GameScene& scene);
    void setMapCell(const int x, const int y, const GLOBAL::CELL_TYPE& cell);
    GLOBAL::CELL_TYPE mapCell(int x, int y) const;
    void setMapSize(const int new_size);
    void updateMapSketch(const int current_level);

    QRgb getMapSketchPixel(const int x, const int y) const;
    void convertFromSketch(int currentLevel);
    void printMap();
private:
    QImage m_mapSketch;

    QPixmap m_cellSprite;

    QPixmap m_mapTexture;

    GLOBAL::Map m_map;
    static const QMap<QRgb, QPoint> colorToPointOfSpriteMap;
};
#endif // MAPMANAGER_H
