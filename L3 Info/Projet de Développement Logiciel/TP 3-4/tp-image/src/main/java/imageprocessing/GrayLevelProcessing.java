package imageprocessing;

import boofcv.alg.color.ColorHsv;
import boofcv.io.image.ConvertBufferedImage;
import boofcv.io.image.UtilImageIO;
import boofcv.struct.image.GrayF32;
import boofcv.struct.image.GrayU8;
import boofcv.struct.image.Planar;
import java.awt.image.BufferedImage;


public class GrayLevelProcessing {

	public static void threshold(Planar<GrayU8> input, int t) {
		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				for (int band = 0; band < input.getNumBands(); ++band) {
					int gl = input.getBand(band).get(x, y);
					if (color < t) {
						color = 0;
					} else {
						color = 255;
					}
					input.getBand(band).set(x, y, color);
				}
			}
		}
	}

	public static void modifyLuminance(Planar<GrayU8> input, int delta) {
		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				for (int band = 0; band < input.getNumBands(); ++band) {
					int color = input.getBand(band).get(x, y);
					color += delta;
					if (color > 255) {
						color = 255;
					}
					input.getBand(band).set(x, y, color);
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

	public static void filterHSV(Planar<GrayF32> input, int h) {
		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				input.getBand(0).set(x, y, h);
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
		//GrayU8 input = UtilImageIO.loadImage(inputPath, GrayU8.class);
		BufferedImage input = UtilImageIO.loadImage(inputPath);
		Planar<GrayU8> image = ConvertBufferedImage.convertFromPlanar(input, null, true, GrayU8.class);
        Planar<GrayF32> output = new Planar<>(GrayF32.class, image.width, image.height, 3);
		if(input == null) {
			System.err.println("Cannot read input file '" + inputPath);
			System.exit(-1);
		}

		// processing
		
        //threshold(image, 128);
		//modifyLuminance(image, 100);
		//dynamicExtension(input);
		//dynamicExtensionOptimized(input);
		//histogramEqualization(input);
		Planar<GrayF32> imageF32 = ConvertBufferedImage.convertFromPlanar(input, null, true, GrayF32.class);
		ColorHsv.rgbToHsv(imageF32, output);
		filterHSV(output, 270);
		
		// save output imagez
		ColorHsv.hsvToRgb(output, output);
		final String outputPath = args[1];
		UtilImageIO.saveImage(output, outputPath);
		System.out.println("Image saved in: " + outputPath);
	}

}