import spidev
import queue as q
import threading as t
from time import sleep, time_ns


class Speaker:
    _dac_mode = 0x00
    queue = q.Queue()

    _lock = t.Lock()
    _running = False
    _thread = None

    def __init__(self, bus: int = 0, device: int = 0, sampling_frequency: int = 200e3) -> None:
        """Initialize SPI speaker with given sampling frequency

        Args:
            bus (int, optional): Id of the SPI Bus. Defaults to 0.
            device (int, optional): Id of the SPI Device (Chip Select). Defaults to 0.
            sampling_frequency (int, optional): Sampling frequency of the speaker (for loop). Defaults to 200e3.
        """

        self.spi = spidev.SpiDev()
        self.spi_config = (bus, device)
        self.sampling_frequency = sampling_frequency

    def open(self) -> None:
        """Open SPI device
        """

        self.spi.open(*self.spi_config)
        self.spi.mode = 0b00            # Write DAC
        self.spi.lsbfirst = False       # MSB First
        self.spi.max_speed_hz = int(10e6)    # 10MHz max speed

    def write_data_point(self, data: int) -> None:
        """Write single sample to speaker

        Args:
            data (int): Speaker value between 0 and 4096
        """

        msb_data = data >> 4
        lsb_data = (data & 0x000F) << 4

        dac_data = [self._dac_mode, msb_data, lsb_data] 

#        print(dac_data)

        self.spi.writebytes(dac_data)

    def create_write_loop(self):
        """Create write loop as new thread

        Raises:
            Exception: Loop is already running

        Returns:
            Queue: Queue from wich the samples are send to the speaker
        """
        with self._lock:
            if self._running:
                raise Exception(
                    f"Write loop for spi device {self.spi_config} already running")

            self._running = True

        self._thread = t.Thread(target=self._write_loop,
                                args=(self.sampling_frequency, self.queue))
        self._thread.start()

        return self.queue

    def _write_loop(self, f: int, q: q.Queue):
        """Write samples to the speaker in a loop

        Args:
            f (int): Samplingfrequency
        """

        sleep_ns = 1/f * 1e9
        last_ns = time_ns()
        data = 0

        while self._running:
            data: int = self.queue.get()

            if (data is None):
                data = 0

            self.write_data_point(data)

            should_sleep_ns = sleep_ns - (time_ns() - last_ns)
            should_sleep_ns = 0 if should_sleep_ns < 0 else should_sleep_ns
            print(should_sleep_ns)
            sleep(should_sleep_ns * 1e-9)
            last_ns = time_ns()

    def stop_write_loop(self):
        """Stop thread in wich the write loop is running. Clear the queue
        """

        with self._lock:
            if not self._running:
                return

            self._running = False

        # Clear queue
        with self.queue.mutex:
            self.queue.queue.clear()
            self.queue.all_tasks_done.notify_all()
            self.queue.unfinished_tasks = 0
        self._thread.join()

    def close(self) -> None:
        """Close spi device. (Stops write loop if necessary)

        Device is automatically closed when Object is destroyed.
        """

        self.stop_write_loop()
        self.spi.close()

    def __del__(self) -> None:
        """Close spi device
        """

        self.close()


if __name__ == "__main__":
    try:
        dev = Speaker(0, 0)
        dev.open()
#        q = dev.create_write_loop()

        while True:
#            q.put(10)
#            q.put(500)
#            q.put(2500)
#            res = dev.write_data_point(10)
            start = time_ns()
            res = dev.write_data_point(500)
            print(time_ns() - start)
#            res = dev.write_data_point(2500)
#            print("write data")
#            print(q.qsize())
#            sleep(1/200e3 * 3)
    except KeyboardInterrupt:
        print("Keyboard interrupt")

    dev.close()
