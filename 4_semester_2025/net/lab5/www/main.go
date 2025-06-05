package main

import (
	"net/http"
	"path/filepath"

	"github.com/gin-gonic/gin"
)

func main() {
	router := gin.Default()

	router.GET("/", func(c *gin.Context) {
		http.ServeFile(c.Writer, c.Request, "index.html")
	})

	router.GET("/:path", func(c *gin.Context) {
		path := c.Param("path")

		cleanPath := filepath.Clean(path)
		if _, err := filepath.Abs(cleanPath); err != nil {
			c.Status(http.StatusNotFound)
			return
		}

		http.ServeFile(c.Writer, c.Request, cleanPath)
	})

	router.Run(":8080")
}
