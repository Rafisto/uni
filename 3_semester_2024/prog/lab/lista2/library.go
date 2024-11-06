package main

import "errors"

type Book struct {
	ID     int    `json:"id" example:"1"`
	Title  string `json:"title" example:"The C Programming Language"`
	Author string `json:"author" example:"Kernighan Ritchie"`
}

type BookCopy struct {
	CopyID   int `json:"copy_id" example:"1"`
	BookID   int `json:"book_id" example:"1"`
	ReaderID int `json:"reader_id" example:"1"`
}

func (bc *BookCopy) IsAvailable() bool {
	return bc.ReaderID == 0
}

func (bc *BookCopy) Borrow(readerID int) error {
	if !bc.IsAvailable() {
		return ErrBookCopyNotAvaialble
	}
	bc.ReaderID = readerID
	return nil
}

func (bc *BookCopy) Return(readerID int) error {
	if bc.IsAvailable() || bc.ReaderID != readerID {
		return ErrBookNotBorrowed
	}
	bc.ReaderID = 0
	return nil
}

type Reader struct {
	ReaderID int    `json:"reader_id" example:"1"`
	Name     string `json:"name" example:"John"`
	Surname  string `json:"surname" example:"Doe"`
}

type BookStorage interface {
	GetBooks() ([]*Book, error)
	GetBook(id int) (*Book, error)
	CreateBook(book *Book) error
	DeleteBook(id int) error
	GetCopies() ([]*BookCopy, error)
	GetCopy(id int) (*BookCopy, error)
	CreateCopy(bookID int) (int, error)
	UpdateCopy(*BookCopy) error
	DeleteCopy(id int) error
}

type ReaderStorage interface {
	CreateReader(reader *Reader) error
	DeleteReader(id int) error
	GetReaders() ([]*Reader, error)
	GetReader(id int) (*Reader, error)
}

type LibraryStorage interface {
	BookStorage
	ReaderStorage
}

var (
	ErrBookNotFound         = errors.New("book not found")
	ErrBookCopyNotFound     = errors.New("book copy not found")
	ErrBookCopyNotAvaialble = errors.New("book copy not available")
	ErrBookNotBorrowed      = errors.New("book not borrowed")
	ErrBookAlreadyBorrowed  = errors.New("book already borrowed")
	ErrReaderNotFound       = errors.New("reader not found")
)
