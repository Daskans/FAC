package imageprocessing;

import boofcv.io.image.ConvertBufferedImage;
import boofcv.io.image.UtilImageIO;
import boofcv.struct.image.GrayU8;
import boofcv.struct.image.Planar;
import java.awt.image.BufferedImage;


public class GrayLevelProcessing {

	public static void threshold(Planar<GrayU8> input, int t) {
		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				for (int band = 0; band < input.getNumBands(); ++band) {
					int gl = input.getBand(band).get(x, y);
					if (gl < t) {
						gl = 0;
					} else {
						gl = 255;
					}
					input.getBand(band).set(x, y, gl);
				}
			}
		}
	}

	public static void modifyLuminance(Planar<GrayU8> input, int delta) {
		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				for (int band = 0; band < input.getNumBands(); ++band) {
					int gl = input.getBand(band).get(x, y);
					gl += delta;
					if (gl > 255) {
						gl = 255;
					}
					input.getBand(band).set(x, y, gl);
				}
			}
		}
		
	}

	public static void dynamicExtension(GrayU8 input) {
		int min = 255;
		int max = 0;
		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				int gl = input.get(x, y);
				if (gl < min) {
					min = gl;
				}
				if (gl > max) {
					max = gl;
				}
			}
		}
		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				int gl = input.get(x, y);
				gl = (255 / (max - min))*(gl - min);
				input.set(x, y, gl);
			}
		}
	}

	public static void dynamicExtensionOptimized(GrayU8 input) {
		int min = 255;
		int max = 0;
		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				int gl = input.get(x, y);
				if (gl < min) {
					min = gl;
				}
				if (gl > max) {
					max = gl;
				}
			}
		}
		if (min != max) {
			int[] LUT = new int[256];
			for (int ng = 0; ng < 256; ng ++) {
				LUT[ng] = (255 * (ng - min))/(max - min);
			}
			for (int y = 0; y < input.height; ++y) {
				for (int x = 0; x < input.width; ++x) {
					int gl = input.get(x, y);
					gl = LUT[gl];
					input.set(x, y, gl);
				}
			}
		}
	}
    
	public static void histogramEqualization(GrayU8 input) {
		int[] hist = new int[256];
		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				hist[input.get(x, y)]++;
			}
		}
		int[] cumulHist = new int[256];
		cumulHist[0] = hist[0];
		for (int k = 1; k < 256; k++) {
			cumulHist[k] = cumulHist[k-1] + hist[k];
		}
		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				int gl = input.get(x, y);
				gl = (cumulHist[gl]*255)/input.totalPixels();
				input.set(x, y, gl);
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
		BufferedImage input = UtilImageIO.loadImage(inputPath);
		Planar<GrayU8> image = ConvertBufferedImage.convertFromPlanar(input, null, true, GrayU8.class);
		if(input == null) {
			System.err.println("Cannot read input file '" + inputPath);
			System.exit(-1);
		}

		// processing
		
        //threshold(image, 128);
		//modifyLuminance(image, -50);
		// dynamicExtension(input);
		//dynamicExtensionOptimized(input);
		//histogramEqualization(input);
		
		// save output image
		final String outputPath = args[1];
		UtilImageIO.saveImage(image, outputPath);
		System.out.println("Image saved in: " + outputPath);
	}

}