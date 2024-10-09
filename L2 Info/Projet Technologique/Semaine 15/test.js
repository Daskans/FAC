
/* ******************** global variables ******************** */

var canvas = document.getElementById('mycanvas');
var canvas2 = document.getElementById('mycanvas2');


// load waluigi image
var waluigi = new Image();
waluigi.src = 'Waluigi.png';

// initial position in canvas
var WaluigiX = 0;
var WaluigiY = 0;

/* ******************** register events ******************** */

window.addEventListener('load', windowLoad);
canvas.addEventListener('click', canvasLeftClick);
canvas2.addEventListener('click', canvasLeftClick);

/* ******************** event callback ******************** */

function canvasLeftClick(event) {
    event.preventDefault();
    WaluigiX = event.offsetX;
    WaluigiY = event.offsetY;
    drawCanvas();
}

function windowLoad() {
    drawCanvas();
}

/* ******************** canvas drawing ******************** */

function drawCanvas() {
    var ctx = canvas.getContext('2d');
    var ctx2 = canvas2.getContext('2d');
    var width = canvas.width;
    var height = canvas.height;
    var width2 = canvas2.width;
    var height2 = canvas2.height;

    // clear canvas
    ctx.clearRect(0, 0, width, height);
    ctx2.clearRect(0, 0, width2, height2);

    // skwère
    ctx.save();
    ctx.fillStyle = 'red';
    ctx.fillRect(100, 100, 40, 40);
    ctx.restore();

    // draw lines
    ctx.save();
    ctx.strokeStyle = 'blue';
    ctx.moveTo( 0, 0);
    ctx.lineTo( width, height);
    ctx.moveTo( width, 0);
    ctx.lineTo( 0, height);
    ctx.stroke();
    ctx.restore();

    // draw a centered text
    ctx.save();
    ctx.font = 'bold 20px Arial';
    ctx.fillStyle = 'black';
    ctx.textAlign = 'center';
    ctx.textBaseline = 'middle';
    ctx.fillText('Hello World', width/2, height/2);
    ctx.restore();

    // draw waluigi
    ctx.drawImage(waluigi, WaluigiX, WaluigiY, width, height);

    // draw a second waluigi
    ctx2.drawImage(waluigi, WaluigiX, WaluigiY, width2, height2);
}

let stopFlag = false;

function rotationCycle() {
    stopFlag = false;
    rotation();
}

function stopRotation() {
    stopFlag = true;
}

function rotation(angle = 0) {
    if (stopFlag == true) {
        return;
    }
    angle = angle + 1;
    if (angle > 360) {
        console.log("exit");
        stop();
    }
    ctx.rotation(angle);
    setTimeout(() => {
        return rotation(angle); 
    }, 10);
    
}
// EOF