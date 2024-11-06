package main

import (
	"net/http"
	"strconv"

	"github.com/gin-gonic/gin"
)

type HTTPMessage struct {
	Message string `json:"message"`
}

type HTTPError struct {
	Error string `json:"error"`
}

type HTTPServer struct {
	service *Service
}

type NewBook struct {
	Title  string `json:"title" example:"The C Programming Language"`
	Author string `json:"author" example:"Kernighan Ritchie"`
}

// GetBooksHandler godoc
// @Summary Get all books
// @Description Get all books
// @Tags get
// @Accept json
// @Produce json
// @Success 200 {array} Book
// @Failure 500 {object} HTTPError
// @Router /books [get]
func (h *HTTPServer) GetBooksHandler(c *gin.Context) {
	books, err := h.service.storage.GetBooks()
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, books)
}

// GetBookHandler godoc
// @Summary Get a book
// @Description Get a book
// @Tags get
// @Accept json
// @Produce json
// @Param id path int true "Book ID"
// @Success 200 {object} Book
// @Failure 400 {object} HTTPError
// @Failure 404 {object} HTTPError
// @Router /books/{id} [get]
func (h *HTTPServer) GetBookHandler(c *gin.Context) {
	id, err := strconv.Atoi(c.Param("id"))
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid book ID"})
		return
	}
	book, err := h.service.storage.GetBook(id)
	if err != nil {
		c.JSON(http.StatusNotFound, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, book)
}

// CreateBookHandler godoc
// @Summary Create a new book
// @Description Create a new book
// @Tags create
// @Accept json
// @Produce json
// @Param book body NewBook true "HTTPError object"
// @Success 201 {object} HTTPMessage
// @Failure 400 {object} HTTPError
// @Failure 500 {object} HTTPError
// @Router /books [post]
func (h *HTTPServer) CreateBookHandler(c *gin.Context) {
	var book Book
	if err := c.ShouldBindJSON(&book); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}
	if err := h.service.storage.CreateBook(&book); err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusCreated, gin.H{"message": "book created", "book_id": book.ID})
}

// DeleteBookHandler godoc
// @Summary Delete a book
// @Description Delete a book
// @Tags delete
// @Accept json
// @Produce json
// @Param id path int true "Book ID"
// @Success 200 {object} HTTPMessage
// @Failure 400 {object} HTTPError
// @Failure 500 {object} HTTPError
// @Router /books/{id} [delete]
func (h *HTTPServer) DeleteBookHandler(c *gin.Context) {
	id, err := strconv.Atoi(c.Param("id"))
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid book ID"})
		return
	}
	if err = h.service.storage.DeleteBook(id); err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, gin.H{"message": "book deleted"})
}

// GetAllCopiesHandler godoc
// @Summary Get all copies
// @Description Get all copies
// @Tags get
// @Accept json
// @Produce json
// @Success 200 {array} BookCopy
// @Failure 500 {object} HTTPError
// @Router /copies [get]
func (h *HTTPServer) GetAllCopiesHandler(c *gin.Context) {
	copies, err := h.service.storage.GetCopies()
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, copies)
}

// CreateCopyHandler godoc
// @Summary Create a new copy
// @Description Create a new copy
// @Tags create
// @Accept json
// @Produce json
// @Param id path int true "Book ID"
// @Success 201 {object} HTTPMessage
// @Failure 400 {object} HTTPError
// @Failure 500 {object} HTTPError
// @Router /books/{id}/copies [post]
func (h *HTTPServer) CreateCopyHandler(c *gin.Context) {
	bookID, err := strconv.Atoi(c.Param("id"))
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid book ID"})
		return
	}
	copyID, err := h.service.storage.CreateCopy(bookID)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusCreated, gin.H{"message": "copy added", "copy_id": copyID})
}

// DeleteCopyHandler godoc
// @Summary Delete a copy
// @Description Delete a copy
// @Tags delete
// @Accept json
// @Produce json
// @Param id path int true "Copy ID"
// @Success 200 {object} HTTPMessage
// @Failure 400 {object} HTTPError
// @Failure 500 {object} HTTPError
// @Router /copies/{id} [delete]
func (h *HTTPServer) DeleteCopyHandler(c *gin.Context) {
	id, err := strconv.Atoi(c.Param("id"))
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid copy ID"})
		return
	}
	if err = h.service.storage.DeleteCopy(id); err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, gin.H{"message": "copy deleted"})
}

// BorrowBookHandler godoc
// @Summary Borrow a book
// @Description Borrow a book
// @Tags post
// @Accept json
// @Produce json
// @Param book_id query int true "Book ID"
// @Param reader_id query int true "Reader ID"
// @Success 200 {object} HTTPMessage
// @Failure 400 {object} HTTPError
// @Failure 500 {object} HTTPError
// @Router /borrow [post]
func (h *HTTPServer) BorrowBookHandler(c *gin.Context) {
	book_id, err := strconv.Atoi(c.Query("book_id"))
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	reader_id, err := strconv.Atoi(c.Query("reader_id"))
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	if err := h.service.BorrowBook(book_id, reader_id); err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, gin.H{"status": "book borrowed"})
}

// ReturnBookHandler godoc
// @Summary Return a book
// @Description Return a book
// @Tags post
// @Accept json
// @Produce json
// @Param copy_id query int true "Copy ID"
// @Param reader_id query int true "Reader ID"
// @Success 200 {object} HTTPMessage
// @Failure 400 {object} HTTPErrord
// @Failure 500 {object} HTTPError
// @Router /return [post]
func (h *HTTPServer) ReturnBookHandler(c *gin.Context) {
	copy_id, err := strconv.Atoi(c.Query("copy_id"))
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	reader_id, err := strconv.Atoi(c.Query("reader_id"))
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	if err := h.service.ReturnBook(copy_id, reader_id); err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, gin.H{"status": "book returned"})
}

// GetReadersHandler godoc
// @Summary Get all readers
// @Description Get all readers
// @Tags get
// @Accept json
// @Produce json
// @Success 200 {array} Reader
// @Failure 500 {object} HTTPError
// @Router /readers [get]
func (h *HTTPServer) GetReadersHandler(c *gin.Context) {
	readers, err := h.service.storage.GetReaders()
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, readers)
}

// GetReaderHandler godoc
// @Summary Get a reader
// @Description Get a reader
// @Tags get
// @Accept json
// @Produce json
// @Param id path int true "Reader ID"
// @Success 200 {object} Reader
// @Failure 400 {object} HTTPError
// @Failure 404 {object} HTTPError
// @Failure 500 {object} HTTPError
// @Router /readers/{id} [get]
func (h *HTTPServer) GetReaderHandler(c *gin.Context) {
	id, err := strconv.Atoi(c.Param("id"))
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid reader ID"})
		return
	}
	reader, err := h.service.storage.GetReader(id)
	if err != nil {
		c.JSON(http.StatusNotFound, gin.H{"error": err.Error()})
		return
	}
	bookList, err := h.service.GetCopiesByReader(id)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}

	type ReturnBook struct {
		CopyID int    `json:"copy_id" example:"1"`
		Author string `json:"author" example:"Kernighan Ritchie"`
		Title  string `json:"title" example:"The C Programming Language"`
	}

	list := make([]*ReturnBook, 0)
	for _, book := range bookList {
		list = append(list, &ReturnBook{CopyID: book.CopyID, Author: book.Author, Title: book.Title})
	}

	c.JSON(http.StatusOK, gin.H{"reader": reader, "books": list})
}

type NewReader struct {
	Name    string `json:"name" example:"John"`
	Surname string `json:"surname" example:"Doe"`
}

// CreateReaderHandler godoc
// @Summary Create a new reader
// @Description Create a new reader
// @Tags create
// @Accept json
// @Produce json
// @Param reader body NewReader true "Reader object"
// @Success 201 {object} Reader
// @Failure 400 {object} HTTPError
// @Failure 500 {object} HTTPError
// @Router /readers [post]
func (h *HTTPServer) CreateReaderHandler(c *gin.Context) {
	var reader Reader
	if err := c.ShouldBindJSON(&reader); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}
	if err := h.service.storage.CreateReader(&reader); err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusCreated, reader)
}

// DeleteReaderHandler godoc
// @Summary Delete a reader
// @Description Delete a reader
// @Tags delete
// @Accept json
// @Produce json
// @Param id path int true "Reader ID"
// @Success 200 {object} HTTPMessage
// @Failure 400 {object} HTTPError
// @Failure 500 {object} HTTPError
// @Router /readers/{id} [delete]
func (h *HTTPServer) DeleteReaderHandler(c *gin.Context) {
	id, err := strconv.Atoi(c.Param("id"))
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid reader ID"})
		return
	}
	if err = h.service.storage.DeleteReader(id); err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, gin.H{"status": "reader deleted"})
}
