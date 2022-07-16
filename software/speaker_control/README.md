## Setup

Install gpiozero and pigpio

````
sudo apt install python3-gpiozero -y
sudo apt install python3-pigpio -y
````

Enable pigpio

````
sudo systemctl enable pigpiod
sudo systemctl restart pigpiod
````