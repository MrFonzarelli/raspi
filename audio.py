import time
from src.stream_analyzer import Stream_Analyzer


ear = Stream_Analyzer(
                device=1,
                rate=44100,
                FFT_window_size_ms=80,
                updates_per_second=2000,
                smoothing_length_ms=50,
                n_frequency_bins=600,
                visualize=1,
                verbose=0
            )

fps = 60

last_update = time.time()
while True:
    if (time.time() - last_update) > (1./fps):
        last_update = time.time()
        raw_fftx, raw_fft, binned_fftx, binned_fft = ear.get_audio_features()