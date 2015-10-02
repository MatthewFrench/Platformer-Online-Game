class Map {
  ArrayList<Block> blocks = new ArrayList<Block>();
  float spawnX = 0;
  float spawnY = 0;
  int scale=32;
  Map() {
  }
  void draw() {
      for (int i = 0; i < blocks.size(); i++) {
        Block b = blocks.get(i);
        b.draw();
      }
      fill(255,0,0, 100);
      rect(spawnX*map.scale, spawnY*map.scale, map.scale, map.scale);
      image(gameGfx[1], spawnX*map.scale, spawnY*map.scale);
  }
  Block getBlock(int x, int y) {
    for (int i = 0; i < blocks.size(); i++) {
      Block b = blocks.get(i);
      if (b.x == x && b.y == y) {
        return b;
      }
    }
    return null;
  }
}
