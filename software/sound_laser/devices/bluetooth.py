"""
  Bluetooth Device
"""

from uuid import uuid4
from sound_laser.devices import AudioDevice

import bluetooth

L2CAP_UUID = "0100"


class BluetoothDevice(AudioDevice):

    def __init__(self, adress: str) -> None:
        if not bluetooth.is_valid_address(adress):
            raise ConnectionError(message=f"Invalid adress: {adress}")
        self._adress = adress

    def __init__(self) -> None:
        pass

    def connect(self):
        self._socket = bluetooth.BluetoothSocket(bluetooth.RFCOMM)

        port = 0x1001

        self._socket.bind(("", port))
        self._socket.listen(1)

        bluetooth.advertise_service(self._socket, name="Sound Laser", service_classes=[
                                    bluetooth.AUDIO_SINK_CLASS])

    def read(self, len: int):
        """
          Read specifict number of bytes
        """
