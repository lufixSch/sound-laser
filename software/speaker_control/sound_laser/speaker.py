
from sound_laser.hal.servo import ServoHAL


class SpeakerControl:
    """Control tilting of the speaker
    """

    x_angle = 0
    y_angle = 0

    def __init__(self, x_pin: int, y_pin: int) -> None:
        """Initialize speaker control for both axis

        Args:
            x_pin (int): Pin to wich the servo for tilting around the x axis is connected (12, 13, 18, 19 for hardware PWM)
            y_pin (int): Pin to wich the servo for tilting around the y axis is connected (12, 13, 18, 19 for hardware PWM)
        """

        self._x_servo = ServoHAL(x_pin, False)
        self._y_servo = ServoHAL(y_pin, False)

    def _map_position(self, tilt_angle: float) -> int:
        """Map tilting angle to servo angle

        Args:
            tilt_angle(float): desired tilting angle

        Returns:
            int: servo position in degree
        """

        return int(tilt_angle)

    def tilt_x(self, angle: float):
        """Tilt speaker around the x axis

        Args:
            angle (float): angle in degree
        """

        servo_pos = self._map_position(angle)
        self._x_servo.set_position(servo_pos)
        self.x_angle = angle

    def tilt_y(self, angle: float):
        """Tilt speaker around the y axis

        Args:
            angle (float): angle in degree
        """

        servo_pos = self._map_position(angle)
        self._y_servo.set_position(servo_pos)
        self.y_angle = angle

    def __del__(self):
        self._x_servo.close()
        self._y_servo.close()
