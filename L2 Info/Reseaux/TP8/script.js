function convertion() {
    let elm = document.getElementsByClassName("power");
    elm.textContent = "Hello World test";
    console.log(elm);
}

let ColorInterval;

function startColorCycle() {
    ColorInterval = setInterval(colorfull, 10);
}

function stopColorCycle() {
    clearInterval(ColorInterval);
}

function colorfull() {
    let elm = document.querySelector("h1");
    let elmColor = window.getComputedStyle(elm).getPropertyValue("color");
    let [r, g, b] = elmColor.match(/\d+/g);
    r = parseInt(r);
    g = parseInt(g);
    b = parseInt(b);
    let hue = hueFromRGB(r, g, b);
    hue = (hue + 5) % 360;
    elm.style.color = `hsl(${hue}, 100%, 50%)`;
}

function hueFromRGB(r, g, b) {
    r /= 255;
    g /= 255;
    b /= 255;
    let max = Math.max(r, g, b);
    let min = Math.min(r, g, b);
    let hue;
    if (max == min) {
        hue = 0;
    } else if (max == r) {
        hue = 60 * ((g - b) / (max - min));
    } else if (max == g) {
        hue = 60 * (2 + (b - r) / (max - min));
    } else if (max == b) {
        hue = 60 * (4 + (r - g) / (max - min));
    }
    return hue;
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
    console.log("stopFlag: " + stopFlag);
    let elm = document.querySelector("img");
    angle = angle + 1;
    if (angle > 360) {
        console.log("exit");
        stop();
    }
    elm.style.transform = `rotate(${angle}deg)`;
    setTimeout(() => {
        return rotation(angle); 
    }, 10);
    
}