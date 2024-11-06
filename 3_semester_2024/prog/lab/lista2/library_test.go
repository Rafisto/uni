package main

import (
	"testing"
)

func TestBookCopyIsAvailable(t *testing.T) {
	bc := &BookCopy{}
	if bc.IsAvailable() != true {
		t.Errorf("expected book copy to be available, got unavailable")
	}

	bc.ReaderID = 1
	if bc.IsAvailable() != false {
		t.Errorf("expected book copy to be unavailable, got available")
	}
}

func TestBookCopyBorrow(t *testing.T) {
	bc := &BookCopy{
		ReaderID: 0,
		BookID:   1,
	}

	err := bc.Borrow(1)
	if err != nil {
		t.Errorf("unexpected error when borrowing book copy: %v", err)
	}

	err = bc.Borrow(2)
	if err == nil {
		t.Errorf("expected error when borrowing already borrowed book copy, got nil")
	}

	bc.ReaderID = 1
	err = bc.Borrow(1)
	if err == nil {
		t.Errorf("expected error when borrowing already borrowed book copy, got nil")
	}
}

func TestBookCopyReturn(t *testing.T) {
	bc := &BookCopy{
		ReaderID: 0,
		BookID:   1,
	}

	err := bc.Return(1)
	if err == nil {
		t.Errorf("expected error when returning not borrowed book copy, got nil")
	}

	bc.ReaderID = 1
	err = bc.Return(2)
	if err == nil {
		t.Errorf("expected error when returning not borrowed book copy, got nil")
	}

	err = bc.Return(1)
	if err != nil {
		t.Errorf("unexpected error when returning borrowed book copy: %v", err)
	}
}
