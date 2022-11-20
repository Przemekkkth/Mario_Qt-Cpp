#include "mapmanager.h"
#include <QGraphicsPixmapItem>
#include "../gamescene.h"

const QMap<QRgb, QPoint> MapManager::colorToPointOfSpriteMap={
    {qRgb(146, 219, 0  ), QPoint(5 , 0 )},
    {qRgb(146, 146, 0  ), QPoint(4 , 0 )},
    {qRgb(146, 182, 0  ), QPoint(6 , 0 )},
    {qRgb(70 , 190, 70 ), QPoint(1 , 1 )},
    {qRgb(145, 219, 145), QPoint(0 , 1 )},
    {qRgb(57 , 244, 57 ), QPoint(2 , 1 )},
    {qRgb(142, 234, 142), QPoint(4 , 1 )},
    {qRgb(143, 185, 143), QPoint(3 , 1 )},
    {qRgb(13 , 142,  13), QPoint(5 , 1 )},
    {qRgb(255, 255, 255), QPoint(7 , 0 )},
    {qRgb(240, 240, 240), QPoint(8 , 0 )},
    {qRgb(235, 235, 235), QPoint(9 , 0 )},
    {qRgb(225, 225, 225), QPoint(7 , 1 )},
    {qRgb(215, 215, 215), QPoint(8 , 1 )},
    {qRgb(205, 205, 205), QPoint(9 , 1 )}
};

const QMap<QRgb, GLOBAL::CELL_TYPE> MapManager::colorToCellMap=
{
    {qRgb(182, 73 ,   0), GLOBAL::CELL_TYPE::Brick         },
    {qRgb(255, 255,   0), GLOBAL::CELL_TYPE::Coin          },
    {qRgb(0  , 146,   0), GLOBAL::CELL_TYPE::TopLeftPipe0  },
    {qRgb(0  , 182,   0), GLOBAL::CELL_TYPE::LeftPipe0     },
    {qRgb(0  , 160,   0), GLOBAL::CELL_TYPE::TopRightPipe0 },
    {qRgb(0  , 200,   0), GLOBAL::CELL_TYPE::RightPipe0    },
    {qRgb(255, 73 ,  85), GLOBAL::CELL_TYPE::QuestionBlock },
    {qRgb(255, 146,  85), GLOBAL::CELL_TYPE::QuestionBlock },
    {qRgb(  0,   0,   0), GLOBAL::CELL_TYPE::Wall0         },
    {qRgb(146,  73,   0), GLOBAL::CELL_TYPE::Wall1         }
};

const QMap<GLOBAL::CELL_TYPE, QPoint> MapManager::cellToPointOfSpriteMap=
{
    {GLOBAL::CELL_TYPE::Brick,                  QPoint(0 , 0)},
    {GLOBAL::CELL_TYPE::Coin,                   QPoint(-1,-1)},
    {GLOBAL::CELL_TYPE::TopLeftPipe0,           QPoint(10, 0)},
    {GLOBAL::CELL_TYPE::LeftPipe0,              QPoint(10, 1)},
    {GLOBAL::CELL_TYPE::TopRightPipe0,          QPoint(11, 0)},
    {GLOBAL::CELL_TYPE::RightPipe0,             QPoint(11, 1)},
    {GLOBAL::CELL_TYPE::ActivatedQuestionBlock, QPoint(6 , 1)},
    {GLOBAL::CELL_TYPE::Wall0,                  QPoint(2 , 0)},
    {GLOBAL::CELL_TYPE::Wall1,                  QPoint(3 , 0)}
};

const QList<GLOBAL::CELL_TYPE> MapManager::animatedCells={

};

MapManager::MapManager()
    : 	m_cellSprite(":/res/map16x16.png")
{

}

int MapManager::getMapSketchHeight() const
{
    return m_mapSketch.height();
}

int MapManager::getMapSketchWidth() const
{
    return m_mapSketch.width();
}

int MapManager::getMapWidth() const
{
    return m_map.size();
}



void MapManager::drawMap(const bool drawBackground, const bool underground, const unsigned view_x, GameScene &scene)
{
    //    unsigned short map_end = ceil((Const::SCREEN_WIDTH + view_x) / static_cast<float>(Const::CELL_SIZE));
    //    unsigned short map_height = floor(m_mapSketch.height() / 3.f);
    //    unsigned short map_start = floor(view_x / static_cast<float>(Const::CELL_SIZE));

    //    //We're drawing the coin before drawing the blocks because we want it to appear behind the question block.
    //    if (!drawBackground)
    //    {
    //        for (const Object& questionBlockCoin : m_questionBlockCoins)
    //        {
    //            m_coinAnimation.setPosition(questionBlockCoin.m_x, questionBlockCoin.m_y);
    //            m_coinAnimation.draw(scene);
    //        }
    //    }

    //    for (unsigned short a = map_start; a < map_end; a++)
    //    {
    //        for (unsigned short b = 0; b < map_height; b++)
    //        {
    //            unsigned short sprite_x = 0;
    //            unsigned short sprite_y = 0;


    //            //This code is a big mess.
    //            //But it works.
    //            //Keep that in mind before judging me.
    //            if (drawBackground)
    //            {
    //                QColor pixel = m_mapSketch.pixelColor(a, b + 2 * map_height);
    //                QRgb pixelRGB = m_mapSketch.pixel(a, b + 2 * map_height);
    //                if (255 == pixel.alpha())
    //                {
    //                    if(colorToPointOfSpriteMap.contains(pixelRGB))
    //                    {
    //                        sprite_x = colorToPointOfSpriteMap[pixelRGB].x();
    //                        sprite_y = colorToPointOfSpriteMap[pixelRGB].y();
    //                    }

    //                    QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
    //                    pItem->setPos(Const::SCREEN_RESIZE*Const::CELL_SIZE * a, Const::SCREEN_RESIZE*Const::CELL_SIZE * b);
    //                    //cell_sprite.setTextureRect(sf::IntRect(CELL_SIZE * sprite_x, CELL_SIZE * sprite_y, CELL_SIZE, CELL_SIZE));
    //                    pItem->setPixmap(m_cellSprite.copy(QRect(Const::CELL_SIZE*sprite_x, Const::CELL_SIZE*sprite_y, Const::CELL_SIZE, Const::CELL_SIZE)).scaled(Const::SCREEN_RESIZE*Const::CELL_SIZE, Const::SCREEN_RESIZE*Const::CELL_SIZE));
    //                    scene.addItem(pItem);
    //                    //i_window.draw(cell_sprite);
    //                }
    //            }
    //            else if (Const::CELL::Empty != m_map[a][b])
    //            {
    //                if(animatedCells.contains(m_map[a][b]))
    //                {
    //                    if (Const::CELL::Coin == m_map[a][b])
    //                    {
    //                        m_coinAnimation.setPosition(Const::CELL_SIZE * a, Const::CELL_SIZE * b);
    //                        m_coinAnimation.draw(scene);
    //                        ///m_coinAnimation.draw(i_window);
    //                    }
    //                    else if (Const::CELL::QuestionBlock == m_map[a][b])
    //                    {
    //                        m_questionBlockAnimation.setPosition(Const::CELL_SIZE * a, Const::CELL_SIZE * b);
    //                        m_questionBlockAnimation.draw(scene);
    //                    }
    //                }
    //                else
    //                {
    //                    //Since the underground blocks have a different look, I placed their texture 2 cells below the regular ones in the map texture.
    //                    sprite_y = 2 * underground;

    //                    if (Const::CELL::ActivatedQuestionBlock == m_map[a][b])
    //                    {
    //                        sprite_x = 6;
    //                        sprite_y++;
    //                    }
    //                    //cell_sprite.setTextureRect(sf::IntRect(CELL_SIZE * sprite_x, CELL_SIZE * sprite_y, CELL_SIZE, CELL_SIZE));
    //                    if(cellToPointOfSpriteMap.contains(m_map[a][b]))
    //                    {
    //                        if(cellToPointOfSpriteMap[m_map[a][b]].x() == -1 && cellToPointOfSpriteMap[m_map[a][b]].y() == -1)
    //                        {
    //                            continue;
    //                        }
    //                        sprite_x = cellToPointOfSpriteMap[m_map[a][b]].x();
    //                        sprite_y = cellToPointOfSpriteMap[m_map[a][b]].y();
    //                    }
    //                    QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
    //                    pItem->setPos(Const::SCREEN_RESIZE*Const::CELL_SIZE * a, Const::SCREEN_RESIZE*Const::CELL_SIZE * b);

    //                    pItem->setPixmap(
    //                                m_cellSprite.copy(QRect(Const::CELL_SIZE * sprite_x, Const::CELL_SIZE * sprite_y, Const::CELL_SIZE, Const::CELL_SIZE)).scaled(Const::SCREEN_RESIZE*Const::CELL_SIZE, Const::SCREEN_RESIZE*Const::CELL_SIZE));
    //                    //i_window.draw(cell_sprite);
    //                    scene.addItem(pItem);
    //                }
    //            }
    //        }
    //    }

    //    //Drawing brick particles.
    //    if (!drawBackground)
    //    {
    //        for (const Object& brickParticle : m_brickParticles)
    //        {
    //            QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
    //            pItem->setPos(brickParticle.m_x*Const::SCREEN_RESIZE, brickParticle.m_y*Const::SCREEN_RESIZE);
    //            pItem->setPixmap(m_cellSprite.copy(QRect(0.25f * Const::CELL_SIZE, Const::CELL_SIZE * (0.25f + 2 * underground), 0.5f * Const::CELL_SIZE, 0.5f * Const::CELL_SIZE)).scaled(Const::SCREEN_RESIZE*Const::CELL_SIZE, Const::SCREEN_RESIZE*Const::CELL_SIZE));
    //            //cell_sprite.setTextureRect(sf::IntRect(0.25f * CELL_SIZE, CELL_SIZE * (0.25f + 2 * i_underground), 0.5f * CELL_SIZE, 0.5f * CELL_SIZE));
    //            //i_window.draw(cell_sprite);
    //            scene.addItem(pItem);
    //        }
    //    }
}

void MapManager::drawBackground(int cameraX, GameScene &scene)
{
    unsigned short map_end = ceil((GLOBAL::SCREEN_SIZE.width() + cameraX) / static_cast<float>(GLOBAL::TILE_SIZE.width()));
    unsigned short map_height = floor(m_mapSketch.height() / 3.f);
    unsigned short map_start = floor(cameraX / static_cast<float>(GLOBAL::TILE_SIZE.width()));


    for (unsigned short a = map_start; a < map_end; a++)
    {
        for (unsigned short b = 0; b < map_height; b++)
        {
            unsigned short sprite_x = 0;
            unsigned short sprite_y = 0;


            //This code is a big mess.
            //But it works.
            //Keep that in mind before judging me.

            QColor pixel = m_mapSketch.pixelColor(a, b + 2 * map_height);
            QRgb pixelRGB = m_mapSketch.pixel(a, b + 2 * map_height);
            if (255 == pixel.alpha())
            {
                if(colorToPointOfSpriteMap.contains(pixelRGB))
                {
                    sprite_x = colorToPointOfSpriteMap[pixelRGB].x();
                    sprite_y = colorToPointOfSpriteMap[pixelRGB].y();
                }

                QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
                pItem->setPos(GLOBAL::TILE_SIZE.width() * a, GLOBAL::TILE_SIZE.width() * b);
                //cell_sprite.setTextureRect(sf::IntRect(CELL_SIZE * sprite_x, CELL_SIZE * sprite_y, CELL_SIZE, CELL_SIZE));
                pItem->setPixmap(m_cellSprite.copy(QRect(16*sprite_x, 16*sprite_y, 16, 16)).scaled(GLOBAL::TILE_SIZE.width(), GLOBAL::TILE_SIZE.height()));
                scene.addItem(pItem);
                //i_window.draw(cell_sprite);
            }

        }
    }

}

void MapManager::setMapCell(const int x, const int y, const GLOBAL::CELL_TYPE &cell)
{
    m_map[x][y] = cell;
}

GLOBAL::CELL_TYPE MapManager::mapCell(int x, int y) const
{
    return m_map[x][y];
}

void MapManager::setMapSize(const int new_size)
{
    m_map.clear();
    m_map.resize(new_size);
}

void MapManager::updateMapSketch(const int current_level)
{
    m_mapSketch.load(":/res/LevelSketch" + QString::number(current_level) + ".png");
    //m_mapSketch.convertTo(QImage::Format_RGBA32FPx4);
    qDebug() << "format " << m_mapSketch.format();
}

QRgb MapManager::getMapSketchPixel(const int x, const int y) const
{
    return m_mapSketch.pixel(x, y);
}

void MapManager::convertFromSketch(int currentLevel)
{
    unsigned short map_height;

    updateMapSketch(currentLevel);
    setMapSize(getMapSketchWidth());

    //We divide the height by 3 because the sketch stores the level as 3 layers: blocks, entities, and background tiles.
    map_height = floor(getMapSketchHeight() / 3.f);

    //i_background_color = mapManager.getMapSketchPixel(0, mapManager.getMapSketchHeight() - 1);

    for (unsigned short a = 0; a < getMapSketchWidth(); a++)
    {
        for (unsigned short b = 0; b < 2 * map_height; b++)
        {
            QRgb pixel = getMapSketchPixel(a, b);

            if (b < map_height)
            {
                setMapCell(a, b, GLOBAL::CELL_TYPE::Empty);
                if(MapManager::colorToCellMap.contains(pixel))
                {
                    setMapCell(a, b, MapManager::colorToCellMap[pixel]);
                }
            }
        }
    }
}
