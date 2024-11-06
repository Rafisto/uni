package main

import (
	"net/http"
	"strconv"

	"github.com/gin-gonic/gin"
)

func main() {
	storage := NewInMemoryStorage()
	service := NewService(storage)

	router := gin.Default()

	router.POST("/books", func(c *gin.Context) {
		var book Book
		if err := c.ShouldBindJSON(&book); err != nil {
			c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
			return
		}
		if err := service.storage.bookStorage.CreateBook(&book); err != nil {
			c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
			return
		}
		c.JSON(http.StatusCreated, gin.H{"message": "book created", "book_id": book.ID})
	})

	router.DELETE("/books/:id", func(c *gin.Context) {
		id, err := strconv.Atoi(c.Param("id"))
		if err != nil {
			c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid book ID"})
			return
		}
		if err = service.storage.bookStorage.DeleteBook(id); err != nil {
			c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
			return
		}
		c.JSON(http.StatusOK, gin.H{"message": "book deleted"})
	})

	router.POST("/books/:id/copies", func(c *gin.Context) {
		bookID, err := strconv.Atoi(c.Param("id"))
		if err != nil {
			c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid book ID"})
			return
		}
		copyID, err := service.storage.bookStorage.AddCopy(bookID)
		if err != nil {
			c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
			return
		}
		c.JSON(http.StatusCreated, gin.H{"message": "copy added", "copy_id": copyID})
	})

	router.DELETE("/copies/:id", func(c *gin.Context) {
		id, err := strconv.Atoi(c.Param("id"))
		if err != nil {
			c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid copy ID"})
			return
		}
		if err = service.storage.bookStorage.DeleteCopy(id); err != nil {
			c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
			return
		}
		c.JSON(http.StatusOK, gin.H{"message": "copy deleted"})
	})

	router.GET("/books", func(c *gin.Context) {
		books, err := service.storage.bookStorage.GetBooks()
		if err != nil {
			c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
			return
		}
		c.JSON(http.StatusOK, books)
	})

	router.GET("/books/:id", func(c *gin.Context) {
		id, err := strconv.Atoi(c.Param("id"))
		if err != nil {
			c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid book ID"})
			return
		}
		book, err := service.storage.bookStorage.GetBook(id)
		if err != nil {
			c.JSON(http.StatusNotFound, gin.H{"error": err.Error()})
			return
		}
		c.JSON(http.StatusOK, book)
	})

	router.POST("/borrow", func(c *gin.Context) {
		var req struct {
			BookID   int `json:"book_id"`
			ReaderID int `json:"reader_id"`
		}
		if err := c.ShouldBindJSON(&req); err != nil {
			c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
			return
		}
		if err := service.BorrowBook(req.BookID, req.ReaderID); err != nil {
			c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
			return
		}
		c.JSON(http.StatusOK, gin.H{"status": "book borrowed"})
	})

	router.POST("/return", func(c *gin.Context) {
		var req struct {
			BookID   int `json:"book_id"`
			ReaderID int `json:"reader_id"`
		}
		if err := c.ShouldBindJSON(&req); err != nil {
			c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
			return
		}
		if err := service.ReturnBook(req.BookID, req.ReaderID); err != nil {
			c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
			return
		}
		c.JSON(http.StatusOK, gin.H{"status": "book returned"})
	})

	router.GET("/readers", func(c *gin.Context) {
		readers, err := service.storage.readerStorage.GetReaders()
		if err != nil {
			c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
			return
		}
		c.JSON(http.StatusOK, readers)
	})

	router.GET("/readers/:id", func(c *gin.Context) {
		id, err := strconv.Atoi(c.Param("id"))
		if err != nil {
			c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid reader ID"})
			return
		}
		reader, err := service.storage.readerStorage.GetReader(id)
		if err != nil {
			c.JSON(http.StatusNotFound, gin.H{"error": err.Error()})
			return
		}
		c.JSON(http.StatusOK, reader)
	})

	router.POST("/readers", func(c *gin.Context) {
		var reader Reader
		if err := c.ShouldBindJSON(&reader); err != nil {
			c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
			return
		}
		if err := service.storage.readerStorage.CreateReader(&reader); err != nil {
			c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
			return
		}
		c.JSON(http.StatusCreated, reader)
	})

	router.DELETE("/readers/:id", func(c *gin.Context) {
		id, err := strconv.Atoi(c.Param("id"))
		if err != nil {
			c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid reader ID"})
			return
		}
		if err = service.storage.readerStorage.DeleteReader(id); err != nil {
			c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
			return
		}
		c.JSON(http.StatusOK, gin.H{"status": "reader deleted"})
	})

	// Start the server
	res := router.Run(":8080")
	if res != nil {
		panic(res)
	}
}
