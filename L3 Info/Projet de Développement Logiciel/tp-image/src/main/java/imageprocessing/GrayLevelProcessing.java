package imageprocessing;

import boofcv.io.image.UtilImageIO;
import boofcv.struct.image.GrayU8;


public class GrayLevelProcessing {

	public static void threshold(GrayU8 input, int t) {
		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
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

	public static void modifyLuminance(GrayU8 input, int delta) {
		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				int gl = input.get(x, y);
				gl += delta;
				if (gl > 255) {
					gl = 255;
				}
				input.set(x, y, gl);
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
		
        // threshold(input, 128);
		// modifyLuminance(input, 50);
		// dynamicExtension(input);
		dynamicExtensionOptimized(input);
		
		// save output image
		final String outputPath = args[1];
		UtilImageIO.saveImage(input, outputPath);
		System.out.println("Image saved in: " + outputPath);
	}

}