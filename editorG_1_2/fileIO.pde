String loadedLevel = "level.txt";
void writeLevel() {
  
   PrintWriter output;
  output = createWriter(loadedLevel);
  output.println("scale:"+map.scale+",spawnx:"+map.spawnX+",spawny:"+map.spawnY);
  String blockData = "";
  for (int i = 0; i < map.blocks.size(); i++) {
      Block block = map.blocks.get(i);
      blockData += "b|g:"+block.getGraphic()+",x:"+block.x+",y:"+block.y;
      if (i != map.blocks.size()-1) {blockData+=";";}
  }
  output.println(blockData);
  output.flush(); // Writes the remaining data to the file
  output.close(); // Finishes the file
  println("File saved.");
  
}

void loadLevel() {
  selectInput("Select a level file to load:", "fileSelected");
}

void fileSelected(File file) {
  if (file == null) {
    println("Window was closed or the user hit cancel");
  } else {
    loadedLevel = file.getAbsolutePath();
    println("User selected " + file.getAbsolutePath());
    println("Loading...");
    
    String lines[] = loadStrings (file);
    
    
    //Make the map
    map = new Map();
    //Get the map attributes
    String[] list = split(lines[0], ',');
    for (int i = 0; i < list.length; i++) {
      String[] attrib = split(list[i],':');
      println(attrib[0]);
      if (attrib[0].equals("spawnx")) {map.spawnX = Float.parseFloat(attrib[1]);}
      if (attrib[0].equals("spawny")) {map.spawnY = Float.parseFloat(attrib[1]);}
      if (attrib[0].equals("scale")) {map.scale = Integer.parseInt(attrib[1]);}
    }
    String[] objects = split(lines[1], ';');
    for (int i = 0; i < objects.length; i++) {
      String object = objects[i];
      String[] objectAttribs = split(object, '|');
      if (objectAttribs[0].equals("b")) { //Block
        Block b = new Block(map, 0);
        String[] attribs = split(objectAttribs[1], ",");
        for (int e = 0; e < attribs.length; e++) {
          String[] attribInfo = split(attribs[e], ":");
          if (attribInfo[0].equals("g")) {
            b.setGraphic(Integer.parseInt(attribInfo[1]));
          }
          if (attribInfo[0].equals("x")) {
            b.x = Float.parseFloat(attribInfo[1]);
          }
          if (attribInfo[0].equals("y")) {
            b.y = Float.parseFloat(attribInfo[1]);
          }
        }
        map.blocks.add(b);
      }
    }
    
  }
}

