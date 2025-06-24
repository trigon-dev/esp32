import serial, requests, sys, time

PORT      = sys.argv[1] if len(sys.argv)>1 else 'COM3'
BAUD      = 115200
WEBHOOK   = 'https://discord.com/api/webhooks/XXXX/YYYYYYYYYYYYYYYYYYYY'

ser = serial.Serial(PORT, BAUD, timeout=None)
time.sleep(1)
print(f"Listening on {PORT} → Discord…")

while True:
    b = ser.read(1)
    if not b: continue
    c = b.decode('utf-8', errors='ignore')
    if ord(c) < 32: continue
    r = requests.post(WEBHOOK, json={'content': c}, timeout=5)
    if not r.ok:
        print(f"Failed {r.status_code} for '{c}'")
