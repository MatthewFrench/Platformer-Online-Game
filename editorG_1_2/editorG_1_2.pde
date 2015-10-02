import java.io.File;
  Map map = new Map();
  final int BRUSH_ERASE=0, BRUSH_GRASS=1, BRUSH_TILE = 2, BRUSH_SPAWN=3;
  int brush=BRUSH_GRASS;
  
  float cameraX=0,cameraY=0;
  
  PImage[] gameGfx = new PImage[3];

void setup() {
  frameRate(30);
  size(1000, 700);
  if (frame != null) {
    frame.setResizable(true); //Allows resizing of the level
  }
  background (0);
  gameGfx[0] = loadImage("ground.png");
  gameGfx[1] = loadImage("player1.png");
  gameGfx[2] = loadImage("wall1.png");
  
  textFont(createFont("Georgia", 16));
}

void draw() {
    background(0);
    if (mousePressed) {
      int x = floor((mouseX+cameraX)/map.scale);
      int y = floor((mouseY+cameraY)/map.scale);
        Block b = map.getBlock(x*map.scale,y*map.scale);
        if (brush==BRUSH_ERASE) {
          if (b != null) {map.blocks.remove(b);}
        }
        if (brush==BRUSH_GRASS) {
          if (b != null) {
            b.setGraphic(BLOCK_GFX_GRASS);
          } else {
            b = new Block(map, BLOCK_GFX_GRASS);
            b.x = x*map.scale; b.y = y*map.scale;
            map.blocks.add(b);
          }
        }
        if (brush==BRUSH_TILE) {
          if (b != null) {
            b.setGraphic(BLOCK_GFX_TILE);
          } else {
            b = new Block(map, BLOCK_GFX_TILE);
            b.x = x*map.scale; b.y = y*map.scale;
            map.blocks.add(b);
          }
        }
        if (brush==BRUSH_SPAWN) {
          map.spawnX=x;
          map.spawnY=y;
        }
    }
    for (int x = 0; x < ceil(width/map.scale); x++){
      for (int y = 0; y < ceil(height/map.scale); y++){
          noFill();
          stroke(25);
          rect(x*map.scale, y*map.scale, map.scale, map.scale);
        }
      }
  pushMatrix();
  translate(-cameraX, -cameraY);
  map.draw();
  popMatrix();
  fill(255);
  text("1=Erase, 2=Grass, 3=Tile, 4=Spawn, z=Save, x=Open, ArrowKeys=Camera", 10, height-10);
}

void keyPressed() {
  if (key==CODED) {
    switch(keyCode) {
    case DOWN: 
      cameraY += map.scale;
      break;
    case UP:
      cameraY -= map.scale;
      break;
    case LEFT:
      cameraX -= map.scale;
      break;
    case RIGHT:
      cameraX += map.scale;
      break;
    default:
      // message
      println ("unknown special key");
      }//switch
  } // if
  
  switch(key) {
    case '1': brush = BRUSH_ERASE; break;
    case '2': brush = BRUSH_GRASS; break;
    case '3': brush = BRUSH_TILE; break;
    case '4': brush = BRUSH_SPAWN; break;
    case 'z': writeLevel(); break;
    case 'x': loadLevel(); break;
    case 'a': cameraX -= map.scale; break;
    case 's': cameraY += map.scale; break;
    case 'w': cameraY -= map.scale; break;
    case 'd': cameraX += map.scale; break;
  } //switch
} //keyPressed()
