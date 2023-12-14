const fs = require("fs");
const http = require("http");
const host = 'localhost';
const port = 8080;
const server = http.createServer();

server.on("request", (req, res) => {
    if (req.url === '/image1') {
        const image1 = fs.readFileSync("./image1.html", "utf-8");
        res.end(image1);
    } else if (req.url === '/image2') {
        const image2 = fs.readFileSync("./image2.html", "utf-8");
        res.end(image2);
    } else if (req.url === '/image3') {
        const image3 = fs.readFileSync("./image3.html", "utf-8");
        res.end(image3);
    } else if (req.url === '/image4') {
        const image4 = fs.readFileSync("./image4.html", "utf-8");
        res.end(image4);
    } else if (req.url === '/image5') {
        const image5 = fs.readFileSync("./image5.html", "utf-8");
        res.end(image5);
    } else if (req.url === '/images') {
        const images = fs.readFileSync("./images.html", "ascii");
        res.end(images);
    }  else if (req.url === '/image1_small') {
        const image1_small = fs.readFileSync("./images/image1_small.jpg");
        res.end(image1_small);
    }  else if (req.url === '/image2_small') {
        const image2_small = fs.readFileSync("./images/image2_small.jpg");
        res.end(image2_small);
    }  else if (req.url === '/image3_small') {
        const image3_small = fs.readFileSync("./images/image3_small.jpg");
        res.end(image3_small);
    }  else if (req.url === '/image4_small') {
        const image4_small = fs.readFileSync("./images/image4_small.jpg");
        res.end(image4_small);
    }  else if (req.url === '/image5_small') {
        const image5_small = fs.readFileSync("./images/image5_small.jpg");
        res.end(image5_small);
    } else if (req.url === '/image1j') {
        const image1 = fs.readFileSync("./images/image1.jpg");
        res.end(image1);
    } else if (req.url === '/image2j') {
        const image2 = fs.readFileSync("./images/image2.jpg");
        res.end(image2);
    } else if (req.url === '/image3j') {
        const image3 = fs.readFileSync("./images/image3.jpg");
        res.end(image3);
    } else if (req.url === '/image4j') {
        const image4 = fs.readFileSync("./images/image4.jpg");
        res.end(image4);
    } else if (req.url === '/image5j') {
        const image5 = fs.readFileSync("./images/image5.jpg");
        res.end(image5);
    }    else {
        const index = fs.readFileSync("./index.html", "utf-8");
        res.end(index);
    }
})

server.listen(port, host, () => {
    console.log(`Server running at http://${host}:${port}/`);
});