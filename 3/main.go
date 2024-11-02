package main

import (
    "crypto/tls"
    "fmt"
    "net/http"
    "sync"
    "time"
    "math/rand"
    "encoding/json"
    "bytes"
    "bufio"
    "os"
    "strings"
)

// Color codes
const (
    Reset      = "\033[0m"
    Bold       = "\033[1m"
    Red        = "\033[31m"
    Green      = "\033[32m"
    Yellow     = "\033[33m"
    Blue       = "\033[34m"
    Magenta    = "\033[35m"
    Cyan       = "\033[36m"
    White      = "\033[37m"
    BgBlue     = "\033[44m"
    BgMagenta  = "\033[45m"
)

type XYZ struct {
    X int `json:"x"`
    Y int `json:"y"`
    Z int `json:"z"`
}

func sendRequest(wg *sync.WaitGroup, url string, data []XYZ) {
    defer wg.Done()

    tr := &http.Transport{
        TLSClientConfig: &tls.Config{InsecureSkipVerify: true},
    }
    client := &http.Client{Transport: tr}

    jsonData, err := json.Marshal(data)
    if err != nil {
        fmt.Printf("%sError marshalling JSON: %v%s\n", Red, err, Reset)
        return
    }

    req, err := http.NewRequest("POST", url, bytes.NewBuffer(jsonData))
    if err != nil {
        fmt.Printf("%sError creating request: %v%s\n", Red, err, Reset)
        return
    }
    req.Header.Set("Content-Type", "application/json")

    _, err = client.Do(req)
    if err != nil {
        fmt.Printf("%sError sending request: %v%s\n", Red, err, Reset)
        return
    }
    fmt.Printf("%sRequest sent successfully%s\n", Green, Reset)
}

func generateRandomXYZ(count int) []XYZ {
    data := make([]XYZ, count)
    for i := 0; i < count; i++ {
        data[i] = XYZ{
            X: rand.Intn(256),
            Y: rand.Intn(256),
            Z: rand.Intn(256),
        }
    }
    return data
}

func originalFunction() {
    url := "https://localhost:10873/api/test"
    numRequests := 100
    numData := 450000

    var wg sync.WaitGroup
    wg.Add(numRequests)

    for i := 0; i < numRequests; i++ {
        data := generateRandomXYZ(numData)
        go sendRequest(&wg, url, data)
        time.Sleep(1 * time.Millisecond)
    }

    wg.Wait()
    fmt.Printf("%sAll requests completed%s\n", Green, Reset)
}

func printHeader(title string) {
    width := 50
    border := strings.Repeat("═", width)
    padding := strings.Repeat(" ", (width-len(title))/2)
    
    fmt.Printf("\n%s%s%s%s%s\n", Bold, Cyan, border, Reset, Reset)
    fmt.Printf("%s%s%s%s%s%s%s\n", Bold, BgBlue, White, padding, title, Reset, Reset)
    fmt.Printf("%s%s%s%s%s\n", Bold, Cyan, border, Reset, Reset)
}

func printMenuItem(number, description string) {
    fmt.Printf("%s║%s %s%-3s%s %s║%s %-40s %s║%s\n", 
        Cyan, Reset,
        Yellow, number, Reset,
        Cyan, Reset,
        description,
        Cyan, Reset)
}

func printMenuBorder() {
    fmt.Printf("%s╠═════╬══════════════════════════════════════════════╣%s\n", Cyan, Reset)
}

func printMenuTop() {
    fmt.Printf("%s╔═════╦══════════════════════════════════════════════╗%s\n", Cyan, Reset)
}

func printMenuBottom() {
    fmt.Printf("%s╚═════╩══════════════════════════════════════════════╝%s\n", Cyan, Reset)
}

func terminalMode() {
    scanner := bufio.NewScanner(os.Stdin)
    
    for {
        printHeader("TERMINAL MODE")
        printMenuTop()
        printMenuItem("1", "Start Data Collection")
        printMenuBorder()
        printMenuItem("2", "Check System Status")
        printMenuBorder()
        printMenuItem("3", "Network Test")
        printMenuBorder()
        printMenuItem("4", "Change Settings")
        printMenuBorder()
        printMenuItem("5", "Generate Report")
        printMenuBorder()
        printMenuItem("6", "Exit")
        printMenuBottom()
        fmt.Printf("\n%sEnter your choice:%s ", Magenta, Reset)

        scanner.Scan()
        choice := scanner.Text()

        switch choice {
        case "1":
            printHeader("EXECUTING FUNCTION 1")
            fmt.Printf("%sStarting data collection process...%s\n", Green, Reset)
        case "2":
            printHeader("EXECUTING FUNCTION 2")
            fmt.Printf("%sChecking system status...%s\n", Green, Reset)
        case "3":
            printHeader("EXECUTING FUNCTION 3")
            fmt.Printf("%sRunning network diagnostics...%s\n", Green, Reset)
        case "4":
            printHeader("EXECUTING FUNCTION 4")
            fmt.Printf("%sOpening settings manager...%s\n", Green, Reset)
        case "5":
            printHeader("EXECUTING FUNCTION 5")
            fmt.Printf("%sGenerating system report...%s\n", Green, Reset)
        case "6":
            printHeader("GOODBYE!")
            fmt.Printf("%sExiting program...%s\n", Yellow, Reset)
            return
        default:
            printHeader("ERROR")
            fmt.Printf("%sInvalid selection. Please try again.%s\n", Red, Reset)
        }
        fmt.Printf("\n%sPress Enter to continue...%s ", Magenta, Reset)
        scanner.Scan()
    }
}

func main() {
    printHeader("MAIN MENU")
    printMenuTop()
    printMenuItem("1", "Enter Terminal Mode")
    printMenuBorder()
    printMenuItem("2", "Run Original Function")
    printMenuBottom()
    fmt.Printf("\n%sEnter your choice:%s ", Magenta, Reset)

    scanner := bufio.NewScanner(os.Stdin)
    scanner.Scan()
    choice := scanner.Text()

    switch choice {
    case "1":
        terminalMode()
    case "2":
        originalFunction()
    default:
        printHeader("ERROR")
        fmt.Printf("%sInvalid selection. Program will now exit.%s\n", Red, Reset)
    }
}