from setuptools import setup, find_packages

setup(
    name="Sound Laser",
    version="0.1.0",
    packages=find_packages(include=["sound_laser"]),
    scripts=['bin/sound_laser'],
)
