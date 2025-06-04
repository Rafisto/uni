package main

import (
	"fmt"

	"github.com/gin-gonic/gin"
)

func header(c *gin.Context) {
	fmt.Println("Headers:", c.Request.Header)

	c.JSON(200, gin.H{
		"headers": c.Request.Header,
	})
}

func main() {
	router := gin.Default()

	router.GET("/", header)

	router.Run(":8080")
}
