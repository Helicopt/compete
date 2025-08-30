package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

const (
	MAXN = 200007
	MODP = 1000000007
	INF  = 0x3f3f3f3f
	LINF = 0x3f3f3f3f3f3f3f3f
	PI   = 3.14159265358979323846
	EPS  = 1e-9
)

var a [MAXN]int

func readArray(a []int, n int, scanner *bufio.Scanner) {
	scanner.Scan()
	line := scanner.Text()
	fields := strings.Fields(line)
	for i := 0; i < n; i++ {
		x, _ := strconv.Atoi(fields[i])
		a[i] = x
	}
}

func solve(Ti int, scanner *bufio.Scanner) {
	// fmt.Printf("Case #%d:", Ti) // print the case number

	scanner.Scan()
	n, _ := strconv.Atoi(scanner.Text())
	readArray(a[:n], n, scanner)

	// TODO: do something

	ans := 0
	for i := 0; i < n; i++ {
		ans += a[i]
	}
	fmt.Println(ans) // print the answer
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Split(bufio.ScanLines)

	scanner.Scan()
	T, err := strconv.Atoi(scanner.Text())
	if err != nil {
		T = 1
	}
	for Ti := 1; Ti <= T; Ti++ {
		solve(Ti, scanner)
	}
}
