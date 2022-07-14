from setuptools import setup, find_packages

setup(
    name="Sound Laser",
    author="Lukas Schuettler",
    author_email="lukas.schuettler@edu.fh-joanneum.at",
    version="0.1.0",
    packages=find_packages(include=["sound_laser", ]),
    entry_points={"console_scripts": [
        "movement_control=sound_laser.main:main"]},
    install_requires=[],
    description="Movement control for sound laser",
    long_description=open("README.md").read(),
)
