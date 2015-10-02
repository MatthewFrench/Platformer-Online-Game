final int BLOCK_GFX_NONE = 0, BLOCK_GFX_GRASS = 1, BLOCK_GFX_TILE = 2;
class Block {
  int graphic = 0;
  float x,y;
  Map map;
  Block(Map m, int hasGraphic) {
    map = m;
    graphic = hasGraphic;
  }
  void setGraphic(int hasGraphic) {
    graphic = hasGraphic;
  }
  int getGraphic() {
    return graphic;
  }
  void draw() {
    if (graphic == BLOCK_GFX_GRASS) {
      fill(0,100,0);
      rect(x, y, map.scale, map.scale);
      image(gameGfx[0], x, y);
    }
    if (graphic == BLOCK_GFX_TILE) {
      fill(100,100,0);
      rect(x, y, map.scale, map.scale);
      image(gameGfx[2], x, y);
    }
  }
}
