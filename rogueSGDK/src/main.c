#include <genesis.h>
#include <string.h>
#include <resources.h>


#define MAP_WIDTH 40
#define MAP_HEIGHT 20
#define TEXT_COLOR 5
#define WALL_COLOR 13
#define FLOOR_COLOR 0
#define PLAYER_COLOR 1
#define ATTACK_COLOR 7
#define SNAKE_COLOR 7

char map[MAP_WIDTH][MAP_HEIGHT];
u16 playerX, playerY;
u16 displayX, displayY;
u16 delayCounter;
u16 playerDir;
char noS = 'n';
u16 sCount = 0;
u16 total_sCount = 0;
u16 floorCount = 0;
char tempMapA = ';';
char tempMapB = ';';
char tempMapC = ';';

void delayVBlank(u16 vblanks);
u16 countNeighbors(char type, u16 x, u16 y);
void cellularAuto();
void createMountains(u16 iterations);
void createMountains2(u16 iterations);
void createShore(u16 iterations);
void createShops(u16 iterations);

void initMap(){
    u16 x, y;

    // Initialize the map with walls
    memset(map, '#', sizeof(map));
    for (x = 1; x < MAP_WIDTH - 1; x++) {
            for (y = 1; y < MAP_HEIGHT - 1; y++) {

                if(random() % 2 == 0) map[x][y] = '.';            

                			
            }
        }

}

void randomWalk(char type){
    u16 x, y;
    // Set initial floor positions randomly using random walk algorithm
    u16 startX = MAP_WIDTH / 2;
    u16 startY = MAP_HEIGHT / 2;
    u16 numSteps = (MAP_WIDTH * MAP_HEIGHT) * 2 ; // Adjust this value as needed

    map[startX][startY] = type;
    u16 currentX = startX;
    u16 currentY = startY;

    for (u16 i = 0; i < numSteps; i++) {
    u16 direction = (random() % 4)+1;

    switch (direction) {
        case 0: // Up
            if (currentY >= 1) {
                currentY--;
                map[currentX][currentY] = type;
            }
            break;
        case 1: // Down
            if (currentY <= MAP_HEIGHT - 2) {
                currentY++;
                map[currentX][currentY] = type;
            }
            break;
        case 2: // Left
            if (currentX >= 1) {
                currentX--;
                map[currentX][currentY] = type;
            }
            break;
        case 3: // Right
            if (currentX <= MAP_WIDTH - 2) {
                currentX++;
                map[currentX][currentY] = type;
            }
            break;
    }
}

}

u16 countNeighbors(char type, u16 x, u16 y){
    u16 wallNeighbors = 0;

                // Count neighboring walls
                if (map[x - 1][y] == type) wallNeighbors++;
                if (map[x + 1][y] == type) wallNeighbors++;
                if (map[x][y - 1] == type) wallNeighbors++;
                if (map[x][y + 1] == type) wallNeighbors++;
                if (map[x - 1][y + 1] == type) wallNeighbors++;
                if (map[x + 1][y - 1] == type) wallNeighbors++;
                if (map[x - 1][y - 1] == type) wallNeighbors++;
                if (map[x + 1][y + 1] == type) wallNeighbors++;

        return wallNeighbors;

}

void smoothMap(u16 iterations){
    u16 x, y;
    // Run cellular automata for map refinement
    for (u16 i = 0; i < iterations; i++) { // Number of iterations
        for (x = 1; x < MAP_WIDTH - 1; x++) {
            for (y = 1; y < MAP_HEIGHT - 1; y++) {

                if (map[x][y] == '.' && countNeighbors('.', x, y) <= 1) map[x][y] = '#';
                if (map[x][y] == '.' && (countNeighbors('.', x, y) == 2 || countNeighbors('.', x, y) == 3)) map[x][y] = '.';
                if (map[x][y] == '.' && countNeighbors('.', x, y) >= 4) map[x][y] = '#';
                if (map[x][y] == '#' && countNeighbors('.', x, y) == 3) map[x][y] = '.';
               
								
				}				
            }
        }
}
void createMountains(u16 iterations){
    u16 x, y;
    // Run cellular automata for map refinement
    for (u16 i = 0; i < iterations; i++) { // Number of iterations
        for (x = 1; x < MAP_WIDTH - 1; x++) {
            for (y = 1; y < MAP_HEIGHT - 1; y++) {

                if (map[x][y] == '#' && countNeighbors('.', x, y) >= 4) map[x][y] = ';';
                //if (map[x][y] == '.') map[x][y] = ',';				
				}				
            }
        }

}
void createMountains2(u16 iterations){
    u16 x, y;
    // Run cellular automata for map refinement
    for (u16 i = 0; i < iterations; i++) { // Number of iterations
        for (x = 1; x < MAP_WIDTH - 1; x++) {
            for (y = 1; y < MAP_HEIGHT - 1; y++) {                
                if (map[x][y] == '.') map[x][y] = ',';				
				}				
            }
        }

}
void createShore(u16 iterations){
    u16 x, y;
    // Run cellular automata for map refinement
    for (u16 i = 0; i < iterations; i++) { // Number of iterations
        for (x = 1; x < MAP_WIDTH - 1; x++) {
            for (y = 1; y < MAP_HEIGHT - 1; y++) {                
                if ((map[x][y] == '#')&& countNeighbors('%',x,y) >= 3) map[x][y] = '\'';
                if ((map[x][y] == ',')&& countNeighbors('%',x,y) >= 3) map[x][y] = '\'';
                if ((map[x][y] == ';')&& countNeighbors('%',x,y) >= 3) map[x][y] = '\'';				
				}				
            }
        }

}

void createShops(u16 iterations){
    u16 x, y;
     for (u16 i = 0; i < iterations; i++) {

        for (x = 1; x < MAP_WIDTH - 1; x++) {
                for (y = 1; y < MAP_HEIGHT - 1; y++) {
                    if (map[x][y] == ';' && (random() % 100)>=99) map[x][y] = 'S';         
                    }				
                }

     }
    
}

void generateMap() {
    

    // Initialize the map with walls
    initMap();
    randomWalk('%');  
    randomWalk('%'); 
    randomWalk('%'); 
    randomWalk('%'); 
    smoothMap(3);
    //cellularAuto();
    createMountains(1);
    createMountains2(1);
    createShore(2);
    createShops(4);


		
        


    }
    

void cellularAuto(){
    u16 x, y;
    for (x = 1; x < MAP_WIDTH - 1; x++) {
            for (y = 1; y < MAP_HEIGHT - 1; y++) {
                
				if(map[x][y] == '#'){
					if (countNeighbors('#',x,y) >= 3 || countNeighbors('#',x,y) == 0)
                    map[x][y] = ';';   
				}               

                // Apply cellular automata rules
                         
            }
        }

        

         for (x = 1; x < MAP_WIDTH - 1; x++) {
            for (y = 1; y < MAP_HEIGHT - 1; y++) {
                

				if(map[x][y] == '#'){
                    if (countNeighbors('.',x,y) >= 3 )
                        map[x][y] = '%';
				}  
                                     
            }
        }
}
void drawMap() {
    u16 x, y;

    for (x = 0; x < MAP_WIDTH; x++) {
        for (y = 0; y < MAP_HEIGHT; y++) {
            if (map[x][y] == '#') {
				//VDP_setBackgroundColor(0);
                //VDP_setTextPalette(1); // Set color for walls
            }
			if (map[x][y] == 'T') {
				//VDP_setBackgroundColor(0);
                //VDP_setTextPalette(2); // Set color for walls
            }
			if (map[x][y] == 'S') {
				//VDP_setBackgroundColor(0);
               // VDP_setTextPalette(3); // Set color for walls
            }
			if (map[x][y] == '.') {
				//VDP_setBackgroundColor(0);
               // VDP_setTextPalette(4); // Set color for walls
            }
			 
            VDP_drawText(&map[x][y], x, y);
			
        }
    }
}


void movePlayer(s16 dx, s16 dy) {
    s16 newX = playerX + dx;
    s16 newY = playerY + dy;
    tempMapA = map[newX][newY];
    tempMapC = tempMapB;
    

    char strBuffer[2]; // The buffer size should be at least 2 to accommodate the character and the null terminator
    strBuffer[0] = tempMapC;
    strBuffer[1] = '\0'; // Add the null terminator at the end



	

    if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT && map[newX][newY] != '#'&& map[newX][newY] != '%') {
        if(map[newX][newY] == 'S'){
            tempMapA = ';';
			sCount = sCount + 1;
			map[newX][newY] = strBuffer;
		}
		tempMapC = tempMapB;



		VDP_drawText(strBuffer, playerX, playerY);
        playerX = newX;
        playerY = newY;
       
        VDP_drawText("@", playerX, playerY);
        tempMapB = tempMapA;
    }
}


void performMeleeAttack() {
    s16 dx = 0, dy = 0;

    switch (playerDir) {
        case 0: // Up
            dy = -1;
            break;
        case 1: // Down
            dy = 1;
            break;
        case 2: // Left
            dx = -1;
            break;
        case 3: // Right
            dx = 1;
            break;
    }

    u16 attackX = playerX + dx;
    u16 attackY = playerY + dy;

    if ((map[attackX][attackY] != '#')&&(map[attackX][attackY] != '%')) {
        map[attackX][attackY] = '*';
        
        VDP_drawText("*", attackX, attackY);
        u16 timer = 5; // Set the duration of the attack symbol

        while (timer > 0) {
            if (delayCounter == 0) {
                delayVBlank(1);
                timer--;
        }
        SYS_doVBlankProcess();
        // Remove the attack symbol after the specified duration
        map[attackX][attackY] = ';';
    
        VDP_drawText(";", attackX, attackY);
    }

    
        
    }
    

    
    
}


void delayVBlank(u16 vblanks) {
    delayCounter = vblanks;
    while (delayCounter > 0) {
        SYS_doVBlankProcess();
    }
}

void vblankCallback() {
    if (delayCounter > 0) {
        delayCounter--;
    }
}

void showMenu() {
    
    VDP_drawText("Press START to generate map", displayX, displayY + 3);
    
    while (1) {
        u16 value = JOY_readJoypad(JOY_1);
        
        if (value & BUTTON_START) {
			VDP_drawText("                            ", displayX, displayY + 3);
            break;  // Exit the menu loop when Start button is pressed
        }
        
        SYS_doVBlankProcess();
    }
}

void countS() {
    u16 x, y;
    

    for (x = 0; x < MAP_WIDTH; x++) {
        for (y = 0; y < MAP_HEIGHT; y++) {
            if (map[x][y] == 'S') {
                total_sCount++;
            }
        }
    }

     
}
void countNoS() {
    u16 x, y;
    u16 count = 0;

    for (x = 0; x < MAP_WIDTH; x++) {
        for (y = 0; y < MAP_HEIGHT; y++) {
            if (map[x][y] == 'S') {
                count++;
            }

        }
    }
	if (count == 0){
		noS = 'y';
	}

     
}



int main() {
	VDP_loadFontData(tileset_Font_Namco_Gradient1.tiles, 96, CPU);
    showMenu();
	sCount = 0;
    generateMap();
    drawMap();
	countS();

    playerX = MAP_WIDTH / 2;
    playerY = MAP_HEIGHT / 2;
    displayX = 1;
    displayY = 20;

    //PAL_setPalette(PAL0,bg1.palette->data, DMA);
    PAL_setPalette(PAL0,palette_Font_Namco_Gradient1.data, DMA);
    
    VDP_drawText("@", playerX, playerY);
    
    VDP_drawText("Sega Genesis ASCII Rogue-Like Demo", displayX, displayY);
    VDP_drawText("by Bear Made Games", displayX, displayY + 1);
	
    VDP_drawText("sCount = ", displayX, displayY + 2);
	VDP_drawText("total sCount = ", displayX, displayY + 3);
	VDP_drawText("floorCount = ", displayX, displayY + 4);
	
    delayCounter = 0;
    SYS_setVIntCallback(vblankCallback);

    while (1) {
		//countNoS();
        u16 value = JOY_readJoypad(JOY_1);
		

		char numberString[3]; // Assuming the number will fit in 5 digits
		char numberString2[3];
		char numberString3[3];
    // Convert the number to a string
    	sprintf(numberString, "%u", sCount);
		sprintf(numberString2, "%u", total_sCount);
		sprintf(numberString3, "%u", floorCount);

		VDP_drawText(numberString, displayX + 9, displayY + 2);
		VDP_drawText(numberString2, displayX + 15, displayY + 3);
		VDP_drawText(numberString3, displayX + 13, displayY + 4);
		
        if (value & BUTTON_UP) {
            if (delayCounter == 0) {
                movePlayer(0, -1);
                playerDir = 0; // Set the player's direction to up
                delayVBlank(5);
            }
        } else if (value & BUTTON_DOWN) {
            if (delayCounter == 0) {
                movePlayer(0, 1);
                playerDir = 1; // Set the player's direction to down
                delayVBlank(5);
            }
        } else if (value & BUTTON_LEFT) {
            if (delayCounter == 0) {
                movePlayer(-1, 0);
                playerDir = 2; // Set the player's direction to left
                delayVBlank(5);
            }
        } else if (value & BUTTON_RIGHT) {
            if (delayCounter == 0) {
                movePlayer(1, 0);
                playerDir = 3; // Set the player's direction to right
                delayVBlank(5);
            }
        } else if (value & BUTTON_A) {
            if (delayCounter == 0) {
                performMeleeAttack();
                delayVBlank(5);
            }
        }
		// countNoS();
		// if(noS == 'y'){
		// 	noS = 'n';
		// 	sCount = 0;
		// 	total_sCount = 0;
		// 	floorCount++;
		// 	generateMap();
		// 	drawMap();
		// 	countS();

		// 	playerX = MAP_WIDTH / 2;
		// 	playerY = MAP_HEIGHT / 2;
		// 	displayX = 1;
		// 	displayY = 20;
			
		// 	VDP_drawText("@", playerX, playerY);
			
			
		// }
		// if(sCount == total_sCount){
		// 	sCount = 0;
		// 	noS = 'n';
		// 	total_sCount = 0;
		// 	floorCount++;
		// 	generateMap();
		// 	drawMap();
		// 	countS();

		// 	playerX = MAP_WIDTH / 2;
		// 	playerY = MAP_HEIGHT / 2;
		// 	displayX = 1;
		// 	displayY = 20;
			
		// 	VDP_drawText("@", playerX, playerY);
			
			
			
		// }


        SYS_doVBlankProcess();
    }

    return 0;
}
