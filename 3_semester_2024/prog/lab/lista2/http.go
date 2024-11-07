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
	storage LibraryStorage
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
// @Router /books [get].
func (h *HTTPServer) GetBooksHandler(c *gin.Context) {
	books, err := h.storage.GetBooks()
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
// @Router /books/{id} [get].
func (h *HTTPServer) GetBookHandler(c *gin.Context) {
	id, err := strconv.Atoi(c.Param("id"))
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid book ID"})
		return
	}
	book, err := h.storage.GetBook(id)
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
// @Router /books [post].
func (h *HTTPServer) CreateBookHandler(c *gin.Context) {
	var book Book
	if err := c.ShouldBindJSON(&book); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	if book.Title == "" || book.Author == "" {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Both 'title' and 'author' body fields are required"})
		return
	}

	if err := h.storage.CreateBook(&book); err != nil {
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
// @Router /books/{id} [delete].
func (h *HTTPServer) DeleteBookHandler(c *gin.Context) {
	id, err := strconv.Atoi(c.Param("id"))
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid book ID"})
		return
	}
	if err = h.storage.DeleteBook(id); err != nil {
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
// @Router /copies [get].
func (h *HTTPServer) GetAllCopiesHandler(c *gin.Context) {
	copies, err := h.storage.GetCopies()
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}

	type FullCopy struct {
		CopyID    int  `json:"copy_id"`
		Available bool `json:"available"`
		Book
	}

	fullCopies := make([]*FullCopy, len(copies))
	for i, copy := range copies {
		book, err := h.storage.GetBook(copy.BookID)
		if err != nil {
			c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
			return
		}
		fullCopies[i] = &FullCopy{copy.CopyID, copy.IsAvailable(), *book}
	}

	c.JSON(http.StatusOK, fullCopies)
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
// @Router /books/{id}/copies [post].
func (h *HTTPServer) CreateCopyHandler(c *gin.Context) {
	bookID, err := strconv.Atoi(c.Param("id"))
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid book ID"})
		return
	}
	copyID, err := h.storage.CreateCopy(bookID)
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
// @Router /copies/{id} [delete].
func (h *HTTPServer) DeleteCopyHandler(c *gin.Context) {
	id, err := strconv.Atoi(c.Param("id"))
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid copy ID"})
		return
	}
	if err = h.storage.DeleteCopy(id); err != nil {
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
// @Router /borrow [post].
func (h *HTTPServer) BorrowBookHandler(c *gin.Context) {
	bookID, err := strconv.Atoi(c.Query("book_id"))
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid book ID"})
		return
	}

	readerID, err := strconv.Atoi(c.Query("reader_id"))
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid reader ID"})
		return
	}

	_, err = h.storage.GetBook(bookID)
	if err != nil {
		c.JSON(http.StatusNotFound, gin.H{"error": "Book not found"})
	}

	_, err = h.storage.GetReader(readerID)
	if err != nil {
		c.JSON(http.StatusNotFound, gin.H{"error": "Reader not found"})
	}

	copies, err := h.storage.GetCopies()
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Failed to get copies"})
		return
	}

	availableCopyID := 0
	for _, copy := range copies {
		if copy.BookID == bookID {
			if copy.ReaderID == readerID {
				c.JSON(http.StatusBadRequest, gin.H{"error": "Book already borrowed by this reader"})
				return
			}
			if copy.IsAvailable() {
				availableCopyID = copy.CopyID
			}
		}
	}

	if availableCopyID == 0 {
		c.JSON(http.StatusNotFound, gin.H{"error": "No available copy"})
		return
	}

	availableCopy, err := h.storage.GetCopy(availableCopyID)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Failed to get copy"})
		return
	}

	err = availableCopy.Borrow(readerID)
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	err = h.storage.UpdateCopy(availableCopy)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Failed to update copy"})
		return
	}

	c.JSON(http.StatusOK, gin.H{"status": "book borrowed", "copy_id": availableCopyID})
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
// @Failure 400 {object} HTTPError
// @Failure 500 {object} HTTPError
// @Router /return [post].
func (h *HTTPServer) ReturnBookHandler(c *gin.Context) {
	copyID, err := strconv.Atoi(c.Query("copy_id"))
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid copy ID"})
		return
	}

	readerID, err := strconv.Atoi(c.Query("reader_id"))
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid reader ID"})
		return
	}

	bookCopy, err := h.storage.GetCopy(copyID)
	if err != nil || bookCopy.ReaderID != readerID {
		c.JSON(http.StatusNotFound, gin.H{"error": "Copy not found or not borrowed by this reader"})
		return
	}

	err = bookCopy.Return(readerID)
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	if err := h.storage.UpdateCopy(bookCopy); err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Failed to return book"})
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
// @Router /readers [get].
func (h *HTTPServer) GetReadersHandler(c *gin.Context) {
	readers, err := h.storage.GetReaders()
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
// @Router /readers/{id} [get].
func (h *HTTPServer) GetReaderHandler(c *gin.Context) {
	id, err := strconv.Atoi(c.Param("id"))
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid reader ID"})
		return
	}

	reader, err := h.storage.GetReader(id)
	if err != nil {
		c.JSON(http.StatusNotFound, gin.H{"error": "Reader not found"})
	}

	copies, err := h.storage.GetCopies()
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}

	type FullCopy struct {
		Book
		BookCopy
	}

	var borrowedBooks []*FullCopy
	for _, copy := range copies {
		if copy.ReaderID == id {
			book, err := h.storage.GetBook(copy.BookID)
			if err == nil {
				borrowedBooks = append(borrowedBooks, &FullCopy{*book, *copy})
			}
		}
	}

	c.JSON(http.StatusOK, gin.H{"reader": reader, "books": borrowedBooks})
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
// @Router /readers [post].
func (h *HTTPServer) CreateReaderHandler(c *gin.Context) {
	var reader Reader
	if err := c.ShouldBindJSON(&reader); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	if reader.Name == "" || reader.Surname == "" {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Both 'name' and 'surname' body fields are required"})
		return
	}

	if err := h.storage.CreateReader(&reader); err != nil {
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
// @Router /readers/{id} [delete].
func (h *HTTPServer) DeleteReaderHandler(c *gin.Context) {
	id, err := strconv.Atoi(c.Param("id"))
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid reader ID"})
		return
	}
	if err = h.storage.DeleteReader(id); err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, gin.H{"status": "reader deleted"})
}
