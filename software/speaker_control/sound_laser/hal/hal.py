from abc import ABC, abstractmethod


class HAL(ABC):
    """
      Base class for every HAL class
    """

    @abstractmethod
    def __init__(self):
        """
          initialize the needed io
        """

    @abstractmethod
    def close(self):
        """
          reset/unregister the different io used in this class
        """
