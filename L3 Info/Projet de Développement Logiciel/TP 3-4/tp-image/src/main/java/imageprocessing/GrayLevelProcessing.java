package imageprocessing;

import boofcv.alg.color.ColorHsv;
import boofcv.io.image.ConvertBufferedImage;
import boofcv.struct.image.Planar;
import java.awt.image.BufferedImage;

import boofcv.io.image.UtilImageIO;
import boofcv.struct.image.GrayU8;
import boofcv.struct.image.Planar;

import boofcv.struct.image.GrayF32;


public class GrayLevelProcessing {

	public static void threshold(GrayU8 input, int t) {
		for (int y = 0; y < input.height; y++) {
			for (int x = 0; x < input.width; x++) {
				int gl = input.get(x, y);
				if (gl < t) {
					gl = 0;
				} else {
					gl = 255;
				}
				input.set(x, y, gl);
			}
		}
	}
	
	public static void thresholdColorTest(Planar<GrayU8> input, int t) {
		for (int i = 0; i < input.getNumBands(); ++i){
			for (int x = 0; x < input.width; x++) {
				for (int y = 0; y < input.height; y++) {
					int gl = input.getBand(i).get(x, y);	
					if (gl < t) {
						gl = 0;
					} else {
						gl = 255;
					}
					input.getBand(i).set(x, y,gl);
				}
			}
		}
	}

	public static void modification_luminosity(GrayU8 image,int delta){
		for(int i = 0 ;i<image.width;i++){
			for(int j = 0 ;j<image.height;j++){
				int pixel = image.get(i, j);
				int newPixel = pixel + delta;
				if (newPixel > 255) {
					newPixel = 255; 
				} else if (newPixel < 0) {
					newPixel = 0;
				}
				image.set(i, j, newPixel);
			}
		}
	}
	
	public static void modification_luminosity_color(Planar<GrayU8> image, int delta) {
		for( int color = 0;color < image.getNumBands() ;color++ ){
			for (int i = 0; i < image.height; i++) {
				for (int j = 0; j < image.width; j++) {
					int pixel = image.getBand(color).get(j, i);
					if ((pixel + delta) <= 255 && (pixel + delta) >= 0) {
						int modification_luminosity = pixel + delta;
						image.getBand(color).set(j, i, modification_luminosity);
					}
					else if ((pixel + delta) > 255){
						int modification_luminosity = 255;
						image.getBand(color).set(j, i, modification_luminosity);
					}
					else if((pixel + delta) < 0) {
						int modification_luminosity = 0;
						image.getBand(color).set(j, i, modification_luminosity);
					}
				}
			}
		}
	}

	public static void extension_image(GrayU8 image){
		int min = image.get(0,0);
		int max = image.get(0,0);
		for (int i = 0; i < image.width; i++) {
			for (int j = 0; j < image.height; j++) {
					int pixel = image.get(i,j);
					if(pixel < min){
						min = image.get(i,j);
					}
					else if(pixel > max){
						max = image.get(i,j);
					}
			}
		}
		for (int i = 0; i < image.width; i++) {
			for (int j = 0; j < image.height; j++) {
				int pixel = image.get(i,j);
				int l_ = (255 * (pixel - min)) / (max - min);
				image.set(i, j, l_);
			}
		}
	}
		
	public static void extension_image_optimal(GrayU8 image){
		int min = image.get(0, 0);
		int max = image.get(0, 0);
		int[] LUT = new int[256] ;
		for (int i = 0; i < image.width; i++) {
			for (int j = 0; j < image.height; j++) {
				int pixel = image.get(i,j);
				if (pixel < min) {
					min = image.get(i,j);
				} else if (pixel > max) {
					max = image.get(i,j);
				}
			}
		}
		for (int i = 0; i < LUT.length; i++) {
			LUT[i] = (255)*(i - min)/(max - min);
		}
		for (int i = 0; i < image.width; i++) {
			for (int j = 0; j < image.height; j++) {
				int pixel = image.get(i,j);
				int l_ = LUT[pixel];
				image.set(i,j, l_);
			}
		}
	}

	public static void extension_image_color(Planar<GrayU8> image) {
		for (int color = 0; color < image.getNumBands(); color++) {
			int min = image.getBand(color).get(0, 0);
			int max = image.getBand(color).get(0, 0);
			for (int i = 0; i < image.height; i++) {
				for (int j = 0; j < image.width; j++) {
					int pixel = image.getBand(color).get(j, i);
					if (pixel < min) {
						min = image.getBand(color).get(j, i);
					} else if (pixel > max) {
						max = image.getBand(color).get(j, i);
					}
				}
			}
			for (int i = 0; i < image.height; i++) {
				for (int j = 0; j < image.width; j++) {
					int pixel = image.getBand(color).get(j, i);
					int l_ = (255 * (pixel - min)) / (max - min);
					image.getBand(color).set(j, i, l_);
				}
			}
		}
	}

	public static void histogram_image(GrayU8 image){
		int[] histo = new int[256];
		for (int i = 0;i<image.height;i++){
			for(int j = 0;j<image.width;j++){
				int pixel = image.get(j,i);
				histo[pixel]++;
			}
		}
		int[] histo_cumul = new int[256];
		histo_cumul[0] = histo[0];
		for (int i = 1;i<histo_cumul.length;i++){
			histo_cumul[i] = histo[i] + histo_cumul[i-1];
		}
		int[] LUT = new int[256];
		for(int i = 0;i<LUT.length;i++){
			LUT[i] = (histo_cumul[i]*255)/(image.height * image.width);
		}
		for (int i = 0; i < image.height; i++) {
			for (int j = 0; j < image.width; j++) {
				int pixel = image.get(j, i);
				int l_ = LUT[pixel];
				image.set(j, i, l_);
			}
		}
	}

	public static void histogram_image_color(Planar<GrayU8> image){
		int[] histo = new int[256];
		for(int color = 0;color < image.getNumBands();color++){
			for (int i = 0;i<image.height;i++){
				for(int j = 0;j<image.width;j++){
					int pixel = image.getBand(color).get(j,i);
					histo[pixel]++;
				}
			}
		}
		int[] histo_cumul = new int[256];
		histo_cumul[0] = histo[0];
		for (int i = 1;i<histo_cumul.length;i++){
			histo_cumul[i] = histo[i] + histo_cumul[i-1];
		}
		int[] LUT = new int[256];
		for(int i = 0;i<LUT.length;i++){
			LUT[i] = (histo_cumul[i]*255)/(image.height * image.width);
		}
		for(int color = 0;color < image.getNumBands();color++){
			for (int i = 0; i < image.height; i++) {
				for (int j = 0; j < image.width; j++) {
					int pixel = image.getBand(color).get(j, i);
					int l_ = LUT[pixel];
					image.getBand(color).set(j, i, l_);
				}
			}
		}
	}

	
	public static void filter_teinter(Planar<GrayF32> input, Planar<GrayF32> output, int teinte){
		if (teinte < 0 || teinte > 360){
		  System.err.println("error value teinte");
		  return;
		}
		for(int x = 0;x<input.width;x++){
		  for(int y = 0;y<input.height;y++){
			float h = input.getBand(0).get(x,y) ;
			float s = input.getBand(1).get(x,y) ;
			float v = input.getBand(2).get(x,y) ;
	
			output.getBand(0).set(x,y,teinte);
			output.getBand(1).set(x,y,s);
			output.getBand(2).set(x,y,v);
		  }
		}
	}
	
	public static void histogramTeintes(Planar<GrayF32> image){
		int[] histo = new int[360];
		for(int i=0; i<image.width;i++){
			for(int j =0; j<image.height; j++){
				int teinte = (int) image.getBand(0).get(i, j);
				if (teinte >= 0 && teinte < 360) {
					histo[teinte]++;
				}
			}
		}
	
		int[] histoCumul = new int[360];
		histoCumul[0] = histo[0];
		for(int i=1; i<histoCumul.length;i++){
			histoCumul[i] = histo[i] + histoCumul[i-1];
		}
	
		int totalPixels = image.width*image.height;
		int[] LUT = new int[360];
		for(int i=0; i<LUT.length;i++){
			LUT[i] = (histoCumul[i] * 359)/totalPixels;
		}
	
		for(int i=0; i < image.width;i++){
			for(int j = 0; j <image.height;j++){
				int teinte = (int) image.getBand(0).get(i, j);
				if (teinte >= 0 && teinte < 360){
				  int newteinte = LUT[teinte];
				  image.getBand(0).set(i, j, newteinte);
				}
			}
		}
	}
	
	  public static void histogram2DTeinteSaturation(Planar<GrayF32> image) {
		int[][] histo2D = new int[360][101]; // 360 car fermée et 101 car 100 ouvert
	
		for(int i = 0; i < image.width; i++){
		  for(int j = 0; j < image.height; j++){
			int teinte = (int) image.getBand(0).get(i,j);  
			float saturation = image.getBand(1).get(i,j);  
			int saturationInt = (int) (saturation * 100);
				
			if (teinte >= 0 && teinte < 360 && saturationInt >= 0 && saturationInt <= 100) {
			  histo2D[teinte][saturationInt]++;
			}
		  }
		}
		GrayU8 output = new GrayU8(360, 101); 
		for(int teinte = 0; teinte < 360; teinte++) {
		  for(int saturation =0; saturation <= 100; saturation++) {
			int value = Math.min(255, (int) (histo2D[teinte][saturation] * 255.0 / (image.width * image.height)));
			output.set(teinte, saturation, value);
		  }
		}
	  }
    

    public static void main( String[] args ) {
    	// load image
		if (args.length < 2) {
			System.out.println("missing input or output image filename");
			System.exit(-1);
		}
		final String inputPath = args[0];
		GrayU8 input = UtilImageIO.loadImage(inputPath, GrayU8.class);
		if(input == null) {
			System.err.println("Cannot read input file '" + inputPath);
			System.exit(-1);
		}

		// processing
		//threshold(input, 128);
        //modification_luminosity(input, 250);
		//extension_image(input);
		//extension_image_optimal(input);
		//histogram_image(input);	

		//COLOR
		BufferedImage input_color = UtilImageIO.loadImage(inputPath);
		Planar<GrayU8> image = ConvertBufferedImage.convertFromPlanar(input_color, null, true, GrayU8.class);
		// thresholdColorTest(image);
		// modification_luminosity_color(image,50);
		// extension_image_color(image);
		// histogram_image_color(image);
		
		// Planar<GrayF32> image_hsv =  ConvertBufferedImage.convertFromPlanar(input_color, null, true,GrayF32.class);	
		// Planar<GrayF32> output_hsv = new Planar<>(GrayF32.class, image.width, image.height, 3);

		//ColorHsv.rgbToHsv(image_hsv, output_hsv);
		//BufferedImage outputImage_conversion_RGB = ConvertBufferedImage.convertTo(image_hsv, null, true);
	
		//Planar<GrayF32> output_teinte = new Planar<>(GrayF32.class, image.width, image.height, 3);
		//filter_teinter(output_hsv, output_teinte,270);
		// BufferedImage outputImage = ConvertBufferedImage.convertTo(output_teinte, null, true);
		// BufferedImage outputImage_conversion_RGB = ConvertBufferedImage.convertTo(image_hsv, null, true);
		// histogramTeintes(image_hsv);
		// histogram2DTeinteSaturation(image_hsv);
		
		
		// ColorHsv.hsvToRgb(output_teinte,output_teinte);
		// save output image


		final String outputPath = args[1];
		UtilImageIO.saveImage(image, outputPath);
		// UtilImageIO.saveImage(image, outputPath);
		System.out.println("Image saved in: " + outputPath);
	}

}