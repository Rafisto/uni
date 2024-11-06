package main

import "errors"

type Book struct {
	ID     int    `json:"id"`
	Title  string `json:"title"`
	Author string `json:"author"`
}

type BookCopy struct {
	ID       int `json:"id"`
	BookID   int `json:"book_id"`
	ReaderID int `json:"reader_id"`
}

type Reader struct {
	ID      int    `json:"id"`
	Name    string `json:"name"`
	Surname string `json:"surname"`
}

var (
	ErrBookNotFound        = errors.New("book not found")
	ErrBookCopyNotFound    = errors.New("book copy not found")
	ErrBookNotBorrowed     = errors.New("book not borrowed")
	ErrBookAlreadyBorrowed = errors.New("book already borrowed")
	ErrReaderNotFound      = errors.New("reader not found")
)

type LibraryService interface {
	BorrowBook(bookID int, readerID int) error
	ReturnBook(bookID int, readerID int) error
	CreateBook(book *Book) error
	DeleteBook(id int) error
	AddCopy(bookID int) (int, error)
	DeleteCopy(id int) error
	GetBooks() ([]*Book, error)
	GetBook(id int) (*Book, error)
	GetReaders() ([]*Reader, error)
	GetReader(id int) (*Reader, error)
	CreateReader(reader *Reader) error
	DeleteReader(id int) error
}

type BookStorage interface {
	CreateBook(book *Book) error
	DeleteBook(id int) error
	AddCopy(bookID int) (int, error)
	DeleteCopy(id int) error
	GetBooks() ([]*Book, error)
	GetBook(id int) (*Book, error)
}

type ReaderStorage interface {
	CreateReader(reader *Reader) error
	DeleteReader(id int) error
	GetReaders() ([]*Reader, error)
	GetReader(id int) (*Reader, error)
}
