const fs = require("fs");
const http = require("http");
const host = 'localhost';
const port = 8080;
const server = http.createServer();

server.on("request", (req, res) => {
    if (req.url === '/images/image1.jpg') {
        const image1 = fs.readFileSync("./images/image1.jpg");
        res.end(image1);
    } else if (req.url === '/images/image2.jpg') {
        const image2 = fs.readFileSync("./images/image2.jpg");
        res.end(image2);
    } else if (req.url === '/images/image3.jpg') {
        const image3 = fs.readFileSync("./images/image3.jpg");
        res.end(image3);
    } else if (req.url === '/3images') {
        const images = fs.readFileSync("./3images.html", "utf-8");
        res.end(images);
    } else if (req.url === '/all-images') {
        const images = fs.readdirSync("./images");
        let pageHTML = "<!DOCTYPE html><html><body>";//let pageHTML = "<!DOCTYPE html><html><body>";
        for (let i = 0; i < images.length; i++) {
            if (!images[i].endsWith("_small.jpg"))
            { 
                pageHTML += fs.readFileSync("./images/"+(images[i].toString()));
            }
        }
        res.end(pageHTML);
    } else {
        const index = fs.readFileSync("./index.html", "utf-8");
        res.end(index);
    }
})

server.listen(port, host, () => {
    console.log(`Server running at http://${host}:${port}/`);
});