import os
from RPLCD.i2c import CharLCD
import RPi.GPIO as GPIO
import psutil
import socket
import time
import subprocess
import tm1637
from datetime import datetime

tm = tm1637.TM1637(clk=16, dio=20)
tm.brightness(7)

GPIO.setmode(GPIO.BCM)
GPIO.setup(21, GPIO.OUT)
GPIO.output(21, GPIO.HIGH)

GPIO.setup(26, GPIO.OUT)
GPIO.output(26, GPIO.HIGH)

networks = ["giovannibr", "RESNET-BROTECTED", "UCSD-PROTECTED"]

def update_time():
    current_time = datetime.now()
    hours = current_time.hour
    minutes = current_time.minute
    
    tm.numbers(hours, minutes)


def get_wifi_ssid():
    result = subprocess.run(['iwconfig'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    
    output = result.stdout.decode('utf-8')
    
    for line in output.split('\n'):
        if "ESSID" in line:
            if len(line.split('"')) > 1:
                ssid = line.split('"')[1]
                return ssid

    return "No WiFi"


def get_wlan0_ip():
    addrs = psutil.net_if_addrs()

    if 'wlan0' in addrs:
        for addr in addrs['wlan0']:
            if addr.family == socket.AF_INET:
                return addr.address
    return ""


def display_wifi_ip(network, ip_address):
    lcd.clear()
    lcd.write_string(network)
    lcd.crlf()
    lcd.write_string(ip_address)


def display_selected_network(pos):
    network = networks[pos]

    lcd.clear()
    lcd.write_string("Select network:")
    lcd.crlf()

    lcd.write_string(network)


def switch_network(pos):
    network = networks[pos]

    os.system(f"""sudo wpa_cli select_network "$(sudo wpa_cli list_networks | grep '{network}' | awk '{{print $1}}')" """)
    time.sleep(2)


lcd = CharLCD(i2c_expander='PCF8574', address=0x27, port=1,
              cols=16, rows=2, charmap='A00', auto_linebreaks=True)

lcd.clear()

ip_address = ""
network = ""

selecting = False
selectingStamp = time.time()

loopStamp = time.time()

knob_CLK = 6
knob_DT = 13
knob_SW = 19

GPIO.setup(knob_CLK, GPIO.IN)
previous_CLK = GPIO.input(knob_CLK)
current_CLK = 0

GPIO.setup(knob_DT, GPIO.IN)
GPIO.setup(knob_SW, GPIO.IN, pull_up_down=GPIO.PUD_UP)
pos = 0

while(True):

    if time.time() - loopStamp > 1.0:
        loopStamp = time.time()

        if ip_address != get_wlan0_ip() or network != get_wifi_ssid():
            ip_address = get_wlan0_ip()
            network = get_wifi_ssid()
            display_wifi_ip(network, ip_address)

    current_CLK = GPIO.input(knob_CLK)

    if current_CLK and not previous_CLK:
        if GPIO.input(knob_DT):
            pos += 1

        else:
            pos -= 1

        pos %= len(networks)
        display_selected_network(pos)
        timeStamp = time.time()
        selecting = True

    if selecting and time.time() - timeStamp > 5.0:
        selecting = False
        display_wifi_ip(network, ip_address)

    if not GPIO.input(knob_SW):
        selecting = False
        switch_network(pos)

    previous_CLK = current_CLK
    update_time()

