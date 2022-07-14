from gpiozero import Servo
from sound_laser.hal import HAL


class ServoHAL(HAL):
    """
        Hardware interface to control a servo
        Attributes:
            pin: number of the GPIO pin used to control the servo
    """

    def __init__(self, pin: int):
        """
            Initialize servo
            Arguments:
                pin: Pin to which the signal wire of the servo is connected (12, 13, 18, 19 for hardware PWM)
        """

        self.pin = pin

        self.pwm = Servo(pin, initial_value=0, min_pulse_width=0.615 /
                         1000, max_pulse_width=2.495 / 1000)

    def setPosition(self, pos: int):
        """
            Set the position of the servo
            Arguments:
                pos: Servoposition between -90 and 90
        """
        self.pwm.value = pos / 90

    def close(self):
        """
            Release servo
        """
        self.pwm.value = None


class ServoInvertedHAL(ServoHAL):
    """
        Hardware interface to control inverted servos
        Attributes:
            pin: number of the GPIO pin used to control the turret
    """

    def setPosition(self, pos: int):
        """
            Trigger Turret with specific force
            Arguments:
                force: Turretposition between -90 and 90
        """

        self.pwm.value = -1 * pos / 90
