
from sound_laser.hal.servo import ServoHAL
import numpy as np
import warnings


class SpeakerControl:
    """Control tilting of the speaker
    """

    x_angle = 0
    y_angle = 0

    l = 20
    d = 64
    r = 90

    def __init__(self, x_pin: int, y_pin: int) -> None:
        """Initialize speaker control for both axis

        Args:
            x_pin (int): Pin to wich the servo for tilting around the x axis is connected (12, 13, 18, 19 for hardware PWM)
            y_pin (int): Pin to wich the servo for tilting around the y axis is connected (12, 13, 18, 19 for hardware PWM)
        """

        self._x_servo = ServoHAL(x_pin, True, 5)
        self._y_servo = ServoHAL(y_pin, True, 10)

        self.x0 = np.sqrt(self.d**2 - self.l**2)

    def _map_position(self, tilt_angle: float) -> float:
        """Map tilting angle to servo angle

        Args:
            tilt_angle(float): desired tilting angle

        Returns:
            int: servo position in degree
        """

        a = np.deg2rad(tilt_angle)

        dx = np.sin(a) * self.r
        x = dx + self.x0

        warnings.filterwarnings("error")
        try:
            phi = np.arccos((self.l**2 + x**2 - self.d**2)/(2 * self.l * x))
        except Warning:
            phi = np.pi/2 - np.sign(a) * np.pi/2

        print(f"sign: {np.sign(a)}, angle: {phi}")
        return np.rad2deg(phi - np.pi/2)

    def tilt_x(self, angle: float):
        """Tilt speaker around the x axis

        Args:
            angle (float): angle in degree
        """

        servo_pos = self._map_position(angle)

        print(f"Tilt X - {servo_pos}")

        self._x_servo.set_position(servo_pos)
        self.x_angle = angle

    def tilt_y(self, angle: float):
        """Tilt speaker around the y axis

        Args:
            angle (float): angle in degree
        """

        servo_pos = self._map_position(angle)

        print(f"Tilt Y - {servo_pos}")

        self._y_servo.set_position(servo_pos)
        self.y_angle = angle

    def __del__(self):
        self._x_servo.close()
        self._y_servo.close()
