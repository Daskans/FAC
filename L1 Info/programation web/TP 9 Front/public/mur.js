console.log('mur.js a été exécuté');
images = document.querySelectorAll('img');
bouton = document.querySelector('button');
display = 'block';
bouton.addEventListener('click', () => {
	if (display=='block') {
		images.forEach((image) => image.style.display = 'inline');
		display = 'inline';
	} else if (display=='inline') {
		images.forEach((image) => image.style.display = 'block');
		display = 'block';
	}
});

let currentImgID = 5;
window.addEventListener('scroll',() => {
    if (currentImgID<=52) {
        currentImgID += 1;
        murImages = document.getElementById('mur-images');
        nouvelleImage = document.createElement('img');
        nouvelleImage.src = '/public/image'+currentImgID+'_small.jpg';
        murImages.appendChild(nouvelleImage);
        images[currentImgID].style.display = display;
    }
})
