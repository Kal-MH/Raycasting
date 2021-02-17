const TILE_SIZE=64;
const MAP_NUM_COLS = 15;
const MAP_NUM_ROWS = 11;

const WINDOW_WIDTH = MAP_NUM_COLS * TILE_SIZE;
const WINDOW_HEIGHT = MAP_NUM_ROWS * TILE_SIZE;

//광선 두께와 광선 수
const WALL_STRIP_WIDTH = 30;
const NUM_RAYS = WINDOW_WIDTH / WALL_STRIP_WIDTH;

//플레이어 시야각
const FOV_ANGLE = 60 * (Math.PI / 180);

//Defining Object
class Map {
    constructor() {
        this.grid = [
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1],
            [1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
        ]
    }

    render() {
        for(var i = 0;i < MAP_NUM_ROWS ; i++){
            for(var j = 0; j < MAP_NUM_COLS; j++){
                var tileX = j * TILE_SIZE;
                var tileY = i  * TILE_SIZE;
                var tileColor = this.grid[i][j] == 1 ? "#222" : "#fff";
                stroke("#222");
                fill(tileColor);
                rect(tileX, tileY, TILE_SIZE, TILE_SIZE);
            }
        }
    }

    hasWallAt(x, y){
        var mapGridIndexX = Math.floor(x / TILE_SIZE);
        var mapGridIndexY = Math.floor(y / TILE_SIZE);

        return this.grid[mapGridIndexY][mapGridIndexX] == 1
    }
}

class Player {
    constructor() {
        this.x = WINDOW_WIDTH / 2;
        this.y = WINDOW_HEIGHT / 2;
        this.radius = 9;
        this.turnDirection = 0;
        this.walkDirection = 0;
        this.rotationAngle = Math.PI / 2;
        this.moveSpeed = 2.0;
        this.rotationSpeed = 2 * (Math.PI / 180);
    }
    render() {
        noStroke();
        fill("red");
        circle(this.x, this.y, this.radius);
        stroke("red");
        // line(
        //     this.x,
        //     this.y,
        //     this.x + (Math.cos(this.rotationAngle) * 50),
        //     this.y + (Math.sin(this.rotationAngle) * 50)
        // )
    }
    update(){
        this.rotationAngle += this.turnDirection * this.rotationSpeed;

        var moveStep = this.walkDirection * this.moveSpeed;

        var newPlayerX = this.x + (Math.cos(this.rotationAngle) * moveStep);
        var newPlayerY = this.y + (Math.sin(this.rotationAngle) * moveStep);
        if (!grid.hasWallAt(newPlayerX, newPlayerY)){
            this.x = newPlayerX;
            this.y = newPlayerY;
        }
    }
}

class Ray {
    //광선은 다 각각 자기의 rayAngle을 가진다.
    constructor(rayAngle) {
        this.rayAngle = normalizeAngle(rayAngle);

        this.wallHitX = 0;
        this.wallHitY = 0;

        this.isRayFacingDown = this.rayAngle > 0 && this.rayAngle < Math.PI;
        this.isRayFacingUp = !this.isRayFacingDown;

        this.isRayFacingLeft = this.rayAngle > (0.5 * Math.PI) && this.rayAngle < (1.5 * Math.PI);
        this.isRayFacingRight = !this.isRayFacingLeft;
    }
    cast(columnId) {
        var xintercept, yintercept;
        var xstep, ystep;

        //Horizontal
        var foundHorzWallHit = false;
        var horWallHitX = 0;
        var horWallHitY = 0;

        yintercept = Math.floor(player.y / TILE_SIZE) * TILE_SIZE;
        yintercept += this.isRayFacingDown ? TILE_SIZE : 0;

        xintercept = player.x + (yintercept - player.y) / Math.tan(this.rayAngle);

        ystep = TILE_SIZE;
        ystep *= this.isRayFacingUp ? -1 : 1;

        xstep = TILE_SIZE / Math.tan(this.rayAngle);
        xstep *= (xstep > 0 && this.isRayFacingLeft) ? -1 : 1;
        xstep *= (xstep < 0 && this.isRayFacingRight) ? -1 : 1;

        var nextHorzTouchX = xintercept;
        var nextHorzTouchY = yintercept;

        /*
         * up일 때, y좌표를 -1해주는 이유는,
         * 절댓값으로 얻어낸 교차점의 좌표들은 grid.hasWallAt함수에서 비교될 때, 
         * 자신들이 걸쳐져 있는 선의 아래 블록에 대해서 벽인지 아닌지 조사하게 된다.
         * 따라서, up일 때 -1을 해주지 않는다면 걸쳐져 있는 선의 아래 블록은 당연히 벽이 아닐 테고, 
         * step을 한 번 더 밟게 되어 벽을 통과하는 광선이 생기게 되는 것이다. 
         */
        // if (this.isRayFacingUp)
        //     nextHorzTouchY--;

        while ((nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_WIDTH) && (nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_HEIGHT)){
            if (grid.hasWallAt(nextHorzTouchX, (this.isRayFacingUp? nextHorzTouchY - 1 : nextHorzTouchY))){
                foundHorzWallHit = true;
                horWallHitX = nextHorzTouchX;
                horWallHitY = nextHorzTouchY;
                break;
            }
            else{
                nextHorzTouchX += xstep;
                nextHorzTouchY += ystep;
            }
        }

        //Vertical
        var foundVertWallHit = false;
        var vertWallHitX = 0;
        var vertWallHitY = 0;

        xintercept = Math.floor(player.x / TILE_SIZE) * TILE_SIZE;
        xintercept += this.isRayFacingRight ? TILE_SIZE : 0;

        yintercept = player.y + (xintercept - player.x) * Math.tan(this.rayAngle);

        xstep = TILE_SIZE;
        xstep *= this.isRayFacingLeft ? -1 : 1;

        ystep = TILE_SIZE * Math.tan(this.rayAngle);
        ystep *= (ystep > 0 && this.isRayFacingUp) ? -1 : 1;
        ystep *= (ystep < 0 && this.isRayFacingDown) ? -1 : 1;

        var nextVertTouchX = xintercept;
        var nextVertTouchY = yintercept;

        /*
         * left일 때, x좌표를 -1해주는 이유는,
         * 절댓값으로 얻어낸 교차점의 좌표들은 grid.hasWallAt함수에서 비교될 때, 
         * 자신들이 걸쳐져 있는 선의 오른쪽 블록에 대해서 벽인지 아닌지 조사하게 된다.
         * 따라서, left일 때 -1을 해주지 않는다면 걸쳐져 있는 선의 오른쪽 블록은 당연히 벽이 아닐 테고, 
         * step을 한 번 더 밟게 되어 벽을 통과하는 광선이 생기게 되는 것이다. 
         */
        //  if (this.isRayFacingLeft)
        //      nextVertTouchX--;

        while ((nextVertTouchX >= 0 && nextVertTouchX <= WINDOW_WIDTH) && (nextVertTouchY >= 0 && nextVertTouchY <= WINDOW_HEIGHT)){
            if (grid.hasWallAt((this.isRayFacingLeft? nextVertTouchX - 1 : nextVertTouchX), nextVertTouchY)){
                foundVertWallHit = true;
                vertWallHitX = nextVertTouchX;
                vertWallHitY = nextVertTouchY;
                break;
            }
            else{
                nextVertTouchX += xstep;
                nextVertTouchY += ystep;
            }
        }

        var horzHitDistance = (foundHorzWallHit)
        ? distanceBetweenPoints(player.x, player.y, horWallHitX, horWallHitY)
        : Number.MAX_VALUE;
        var vertHitDistance = (foundVertWallHit)
        ? distanceBetweenPoints(player.x, player.y, vertWallHitX, vertWallHitY)
        : Number.MAX_VALUE;

        this.wallHitX = (horzHitDistance < vertHitDistance) ? horWallHitX : vertWallHitX
        this.wallHitY = (horzHitDistance < vertHitDistance) ? horWallHitY : vertWallHitY
        this.distance = (horzHitDistance < vertHitDistance) ? horzHitDistance : vertHitDistance

        if (this.distance >= 100){
            this.wallHitX = player.x + Math.cos(this.rayAngle) * 100;
            this.wallHitY = player.y + Math.sin(this.rayAngle) * 100;
        }
    }
    render() {
        stroke("rgba(255, 0, 0, 0.3)")
        line(
            player.x,
            player.y,
            this.wallHitX, 
            this.wallHitY
        )
    }
}

//Object
var grid = new Map();
var player = new Player();
var rays = [];

//function

function distanceBetweenPoints(x1, y1, x2, y2) {
    return Math.sqrt((x2-x1) * (x2-x1) + (y2-y1) * (y2-y1));
    
}

function normalizeAngle(angle){
    angle = angle % (Math.PI * 2);
    if (angle < 0) {
        angle  = angle + (Math.PI * 2);
    }
    return angle;
}

function keyPressed() {
    if (keyCode == UP_ARROW){
        player.walkDirection = 1;
    } else if (keyCode == DOWN_ARROW){
        player.walkDirection = -1;
    } else if (keyCode == RIGHT_ARROW){
        player.turnDirection = 1;
    } else if (keyCode == LEFT_ARROW){
        player.turnDirection = -1;
    }
}

function keyReleased() {
    if (keyCode == UP_ARROW){
        player.walkDirection = 0;
    } else if (keyCode == DOWN_ARROW){
        player.walkDirection = 0;
    } else if (keyCode == RIGHT_ARROW){
        player.turnDirection = 0;
    } else if (keyCode == LEFT_ARROW){
        player.turnDirection = 0;
    }
}

function setup() {
    createCanvas(WINDOW_WIDTH, WINDOW_HEIGHT)
}

function castAllRays() {
    var columnId = 0;

    //처음 컬럼의 rayAngle. 즉, 0번째 컬럼의 각을 계산한다.
    var rayAngle = player.rotationAngle - (FOV_ANGLE / 2);

    //매번 새로 만들어줘야 동일한 갯수의 광선만 가질 수 있게 된다.
    //rays를 초기화해주지 않는다면, 이전 광선의 것과 합쳐져서 보이게 된다.
    rays =  [];

    for(var i = 0;i < NUM_RAYS;i++){
        var ray = new Ray(rayAngle);

        ray.cast(columnId)
        rays.push(ray);

        rayAngle += FOV_ANGLE / NUM_RAYS;
        columnId++;
    }
}

function update() {
    player.update();
}

function draw() {
    update();
    
    grid.render();
    player.render();
    for(ray of rays){
        ray.render();
    }
    castAllRays();
}