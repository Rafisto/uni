package main

import (
	"testing"
)

func TestCreateInMemoryStorage(t *testing.T) {
	storage := NewInMemoryStorage()

	if storage == nil {
		t.Errorf("expected reader storage to be initialized, got nil")
	}
}

func TestCreateBook(t *testing.T) {
	storage := NewInMemoryBookStorage()

	book := &Book{Title: "Test Book"}
	err := storage.CreateBook(book)
	if err != nil {
		t.Errorf("unexpected error when creating book: %v", err)
	}
	if book.ID != 1 {
		t.Errorf("expected book ID to be 1, got %d", book.ID)
	}
	if _, exists := storage.books[book.ID]; !exists {
		t.Errorf("expected book with ID 1 to exist, but it does not")
	}
}

func TestDeleteBook(t *testing.T) {
	storage := NewInMemoryBookStorage()

	err := storage.DeleteBook(1)
	if err == nil {
		t.Errorf("expected error when deleting non-existent book, got nil")
	}

	book := &Book{Title: "Test Book"}
	err = storage.CreateBook(book)
	if err != nil {
		t.Fatalf("failed to create book: %v", err)
	}

	err = storage.DeleteBook(book.ID)
	if err != nil {
		t.Errorf("unexpected error when deleting book: %v", err)
	}
	if _, exists := storage.books[book.ID]; exists {
		t.Errorf("expected book with ID %d to be deleted, but it still exists", book.ID)
	}
}

func TestAddCopy(t *testing.T) {
	storage := NewInMemoryBookStorage()

	_, err := storage.CreateCopy(1)
	if err == nil {
		t.Errorf("expected error when adding copy to non-existent book, got nil")
	}

	book := &Book{Title: "Test Book"}
	err = storage.CreateBook(book)
	if err != nil {
		t.Fatalf("failed to create book: %v", err)
	}

	copyID, err := storage.CreateCopy(book.ID)
	if err != nil {
		t.Errorf("unexpected error when adding copy to existing book: %v", err)
	}
	if copyID == 0 {
		t.Errorf("expected non-zero copy ID, got %d", copyID)
	}

	if _, exists := storage.copies[copyID]; !exists {
		t.Errorf("expected copy with ID %d to exist, but it does not", copyID)
	}
}

func TestDeleteCopy(t *testing.T) {
	storage := NewInMemoryBookStorage()

	err := storage.DeleteCopy(1)
	if err == nil {
		t.Errorf("expected error when deleting non-existent copy, got nil")
	}

	book := &Book{Title: "Test Book"}
	err = storage.CreateBook(book)
	if err != nil {
		t.Fatalf("failed to create book: %v", err)
	}

	copyID, err := storage.CreateCopy(book.ID)
	if err != nil {
		t.Fatalf("failed to add copy: %v", err)
	}

	err = storage.DeleteCopy(copyID)
	if err != nil {
		t.Errorf("unexpected error when deleting copy: %v", err)
	}

	if _, exists := storage.copies[copyID]; exists {
		t.Errorf("expected copy with ID %d to be deleted, but it still exists", copyID)
	}
}

func TestGetBooks(t *testing.T) {
	storage := NewInMemoryBookStorage()

	books, err := storage.GetBooks()
	if err != nil {
		t.Errorf("unexpected error when getting books: %v", err)
	}
	if len(books) != 0 {
		t.Errorf("expected no books, got %d", len(books))
	}

	book := &Book{Title: "Test Book"}
	err = storage.CreateBook(book)
	if err != nil {
		t.Fatalf("failed to create book: %v", err)
	}

	books, err = storage.GetBooks()
	if err != nil {
		t.Errorf("unexpected error when getting books: %v", err)
	}
	if len(books) != 1 {
		t.Errorf("expected 1 book, got %d", len(books))
	}
	if books[0].ID != 1 {
		t.Errorf("expected book ID to be 1, got %d", books[0].ID)
	}
	if books[0].Title != "Test Book" {
		t.Errorf("expected book title to be 'Test Book', got %s", books[0].Title)
	}
}

func TestGetBook(t *testing.T) {
	storage := NewInMemoryBookStorage()

	_, err := storage.GetBook(1)
	if err == nil {
		t.Errorf("expected error when getting non-existent book, got nil")
	}

	book := &Book{Title: "Test Book"}
	err = storage.CreateBook(book)
	if err != nil {
		t.Fatalf("failed to create book: %v", err)
	}

	gotBook, err := storage.GetBook(book.ID)
	if err != nil {
		t.Errorf("unexpected error when getting book: %v", err)
	}
	if gotBook.ID != book.ID {
		t.Errorf("expected book ID to be %d, got %d", book.ID, gotBook.ID)
	}
	if gotBook.Title != book.Title {
		t.Errorf("expected book title to be '%s', got '%s'", book.Title, gotBook.Title)
	}
}

func TestCreateReader(t *testing.T) {
	storage := NewInMemoryReaderStorage()

	reader := &Reader{Name: "Test", Surname: "Reader"}
	err := storage.CreateReader(reader)
	if err != nil {
		t.Errorf("unexpected error when creating reader: %v", err)
	}
	if reader.ReaderID != 1 {
		t.Errorf("expected reader ID to be 1, got %d", reader.ReaderID)
	}
	if _, exists := storage.readers[reader.ReaderID]; !exists {
		t.Errorf("expected reader with ID 1 to exist, but it does not")
	}
}

func TestDeleteReader(t *testing.T) {
	storage := NewInMemoryReaderStorage()

	err := storage.DeleteReader(1)
	if err == nil {
		t.Errorf("expected error when deleting non-existent reader, got nil")
	}

	reader := &Reader{Name: "Test", Surname: "Reader"}
	err = storage.CreateReader(reader)
	if err != nil {
		t.Fatalf("failed to create reader: %v", err)
	}

	err = storage.DeleteReader(reader.ReaderID)
	if err != nil {
		t.Errorf("unexpected error when deleting reader: %v", err)
	}
	if _, exists := storage.readers[reader.ReaderID]; exists {
		t.Errorf("expected reader with ID %d to be deleted, but it still exists", reader.ReaderID)
	}
}
