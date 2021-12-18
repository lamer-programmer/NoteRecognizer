from scipy.io import wavfile
import numpy as np
import noisereduce as nr
import os
import argparse

def dir_path(path):
    if os.path.isdir(path):
        return path
    else:
        raise argparse.ArgumentTypeError(f"readable_dir:{path} is not a valid path")

def reduce_noise_wavfile(filepath):
    rate, data = wavfile.read(filepath)
    reduced_noise = nr.reduce_noise(y=data[:, 0], sr=rate,thresh_n_mult_nonstationary=2, prop_decrease=0.9, stationary=False)
    return reduced_noise, rate

def process_folder(path, outpath):
    for subdir, dirs, files in os.walk(path):
        for filename in files:
            filepath = subdir + os.sep + filename

            if filepath.endswith('.wav'):
                print(filename)
                reduced_noise, rate = reduce_noise_wavfile(filepath)
                wavfile.write(outpath + os.sep + filename[:-4] + '_reduced.wav', rate, reduced_noise.astype(np.int16))

def main():
    parser = argparse.ArgumentParser(description='Noise reduction for NoteRecogniser')
    parser.add_argument('-inpath', type=dir_path, help='Input path for wav file(s), can be file or folder', default=os.curdir + os.sep + "to_process")
    parser.add_argument('-outpath', type=dir_path, help='Output path for wav file(s), should be folder', default=os.curdir + os.sep + "reduced")
    args = parser.parse_args()
    process_folder(args.inpath, args.outpath)

if __name__ == '__main__':
   main()