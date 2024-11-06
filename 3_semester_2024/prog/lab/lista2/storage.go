package main

import (
	"sync"
)

var _ BookStorage = (*InMemoryBookStorage)(nil)
var _ ReaderStorage = (*InMemoryReaderStorage)(nil)

type InMemoryStorage struct {
	bookStorage   *InMemoryBookStorage
	readerStorage *InMemoryReaderStorage
}

func NewInMemoryStorage() *InMemoryStorage {
	return &InMemoryStorage{
		bookStorage:   NewInMemoryBookStorage(),
		readerStorage: NewInMemoryReaderStorage(),
	}
}

type InMemoryBookStorage struct {
	books  map[int]*Book
	copies map[int]*BookCopy
	nextID int
	copyID int
	mu     sync.Mutex
}

func NewInMemoryBookStorage() *InMemoryBookStorage {
	return &InMemoryBookStorage{
		books:  make(map[int]*Book),
		copies: make(map[int]*BookCopy),
		nextID: 1,
		copyID: 1,
		mu:     sync.Mutex{},
	}
}

func (s *InMemoryBookStorage) CreateBook(book *Book) error {
	s.mu.Lock()
	defer s.mu.Unlock()

	book.ID = s.nextID
	s.nextID++
	s.books[book.ID] = book
	return nil
}

func (s *InMemoryBookStorage) DeleteBook(id int) error {
	s.mu.Lock()
	defer s.mu.Unlock()

	if _, exists := s.books[id]; !exists {
		return ErrBookNotFound
	}
	delete(s.books, id)
	return nil
}

func (s *InMemoryBookStorage) AddCopy(bookID int) (int, error) {
	s.mu.Lock()
	defer s.mu.Unlock()

	if _, exists := s.books[bookID]; !exists {
		return 0, ErrBookNotFound
	}
	copyID := s.copyID
	s.copyID++
	s.copies[copyID] = &BookCopy{ID: copyID, BookID: bookID, ReaderID: 0}
	return copyID, nil
}

func (s *InMemoryBookStorage) DeleteCopy(id int) error {
	s.mu.Lock()
	defer s.mu.Unlock()

	if _, exists := s.copies[id]; !exists {
		return ErrBookCopyNotFound
	}
	delete(s.copies, id)
	return nil
}

func (s *InMemoryBookStorage) GetBooks() ([]*Book, error) {
	s.mu.Lock()
	defer s.mu.Unlock()

	books := make([]*Book, 0, len(s.books))
	for _, book := range s.books {
		books = append(books, book)
	}
	return books, nil
}

func (s *InMemoryBookStorage) GetBook(id int) (*Book, error) {
	s.mu.Lock()
	defer s.mu.Unlock()

	book, exists := s.books[id]
	if !exists {
		return nil, ErrBookNotFound
	}
	return book, nil
}

type InMemoryReaderStorage struct {
	readers map[int]*Reader
	nextID  int
	mu      sync.Mutex
}

func NewInMemoryReaderStorage() *InMemoryReaderStorage {
	return &InMemoryReaderStorage{
		readers: make(map[int]*Reader),
		nextID:  1,
		mu:      sync.Mutex{},
	}
}

func (s *InMemoryReaderStorage) GetReaders() ([]*Reader, error) {
	s.mu.Lock()
	defer s.mu.Unlock()

	readers := make([]*Reader, 0, len(s.readers))
	for _, reader := range s.readers {
		readers = append(readers, reader)
	}
	return readers, nil
}

func (s *InMemoryReaderStorage) GetReader(id int) (*Reader, error) {
	s.mu.Lock()
	defer s.mu.Unlock()

	reader, exists := s.readers[id]
	if !exists {
		return nil, ErrReaderNotFound
	}

	return reader, nil
}

func (s *InMemoryReaderStorage) CreateReader(reader *Reader) error {
	s.mu.Lock()
	defer s.mu.Unlock()

	reader.ID = s.nextID
	s.nextID++
	s.readers[reader.ID] = reader
	return nil
}

func (s *InMemoryReaderStorage) DeleteReader(id int) error {
	s.mu.Lock()
	defer s.mu.Unlock()

	if _, exists := s.readers[id]; !exists {
		return ErrReaderNotFound
	}
	delete(s.readers, id)
	return nil
}
