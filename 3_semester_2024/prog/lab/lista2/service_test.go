package main

import (
	"errors"
	"testing"
)

func TestBorrowBook(t *testing.T) {
	storage := NewInMemoryStorage()
	service := NewService(storage)

	err := service.storage.CreateReader(&Reader{Name: "Test", Surname: "Reader"})
	if err != nil {
		t.Fatalf("failed to create reader: %v", err)
	}

	// Test borrowing a non-existent book
	err = service.BorrowBook(1, 1)
	if !errors.Is(err, ErrBookNotFound) {
		t.Errorf("expected ErrBookNotFound, got %v", err)
	}

	// Create a book and add a copy
	book := &Book{Title: "Test Book"}
	err = service.storage.CreateBook(book)
	if err != nil {
		t.Fatalf("failed to create book: %v", err)
	}
	copyID, err := service.storage.CreateCopy(book.ID)
	if err != nil {
		t.Fatalf("failed to add copy: %v", err)
	}

	// Test borrowing a book copy
	err = service.BorrowBook(copyID, 1)
	if err != nil {
		t.Errorf("unexpected error when borrowing book: %v", err)
	}

	// Test borrowing an already borrowed book copy
	err = service.BorrowBook(copyID, 1)
	if !errors.Is(err, ErrBookAlreadyBorrowed) {
		t.Errorf("expected ErrBookAlreadyBorrowed, got %v", err)
	}
}

func TestReturnBook(t *testing.T) {
	storage := NewInMemoryStorage()
	service := NewService(storage)

	err := service.storage.CreateReader(&Reader{Name: "Test", Surname: "Reader"})
	if err != nil {
		t.Fatalf("failed to create reader: %v", err)
	}

	err = service.storage.CreateReader(&Reader{Name: "Test2", Surname: "Reader2"})
	if err != nil {
		t.Fatalf("failed to create reader: %v", err)
	}

	// Test returning a non-existent book
	err = service.ReturnBook(1, 1)
	if !errors.Is(err, ErrBookCopyNotFound) {
		t.Errorf("expected ErrBookCopyNotFound, got %v", err)
	}

	// Create a book and add a copy
	book := &Book{Title: "Test Book"}
	err = service.storage.CreateBook(book)
	if err != nil {
		t.Fatalf("failed to create book: %v", err)
	}
	copyID, err := service.storage.CreateCopy(book.ID)
	if err != nil {
		t.Fatalf("failed to add copy: %v", err)
	}

	// Test borrowing a book that does not exist
	err = service.BorrowBook(-1, 1)
	if !errors.Is(err, ErrBookNotFound) {
		t.Errorf("expected ErrBookNotFound, got %v", err)
	}

	// Borrow the book
	err = service.BorrowBook(copyID, 1)
	if err != nil {
		t.Fatalf("failed to borrow book: %v", err)
	}

	// Test returning a book copy
	err = service.ReturnBook(copyID, 1)
	if err != nil {
		t.Errorf("unexpected error when returning book: %v", err)
	}

	// Test returning a book copy that is not borrowed
	err = service.ReturnBook(copyID, 1)
	if !errors.Is(err, ErrBookNotBorrowed) {
		t.Errorf("expected ErrBookNotBorrowed, got %v", err)
	}

	// Test returning a book copy that is borrowed by another reader
	err = service.BorrowBook(copyID, 1)
	if err != nil {
		t.Fatalf("failed to borrow book: %v", err)
	}

	err = service.ReturnBook(copyID, 2)
	if !errors.Is(err, ErrBookNotBorrowed) {
		t.Errorf("expected ErrBookNotBorrowed, got %v", err)
	}
}
