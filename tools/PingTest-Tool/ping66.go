/*
Author: Nhim Roeung
*/

package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"os/exec"
)

func main() {
	address := os.Args[1]
	date := os.Args[2]
	time := os.Args[3]

	ping6(address, date, time)
}

func ping6(address, date, time string) {
	cmd := exec.Command("ping6", "-c", "1000", address)
	out, err := cmd.Output()
	if err != nil {
		fmt.Println(address)
		fmt.Fprintln(os.Stderr, "Error pinging the address", err)
		os.Exit(1)
	}

	file, error := os.Create("pingdata_" + date + "T" + time + ":00" + ".txt")
	check(error)

	err = ioutil.WriteFile("pingdata_"+date+"T"+time+":00"+".txt", out, 0644)

	file.Close()
}

func check(e error) {
	if e != nil {
		panic(e)
	}
}

