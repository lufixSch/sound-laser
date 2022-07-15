from gpiozero.pins.pigpio import PiGPIOFactory
from gpiozero import Device

import argparse
import os.path as path

from sound_laser.server import Server

BASE_PATH = path.abspath(path.dirname(__file__))
WWW_PATH = path.join(path.dirname(BASE_PATH), "www")


def main():
    """ Entrypoint of the movement control programm"""

    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-p", "--port", help="Port on wich the webserver will listen", type=int, default=8080)
    parser.add_argument(
        "-d", "--dir", help="Directory wich includes your html, css and js files", default=WWW_PATH)
    args = parser.parse_args()

    Device.pin_factory = PiGPIOFactory()
    server = Server(args.port, args.dir)
    server.open()


if __name__ == "__main__":
    main()
