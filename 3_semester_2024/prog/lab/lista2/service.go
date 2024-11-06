package main

var _ LibraryService = (*Service)(nil)

type Service struct {
	storage *InMemoryStorage
}

func NewService(storage *InMemoryStorage) *Service {
	return &Service{storage: storage}
}

func (s *Service) BorrowBook(bookID int, readerID int) error {
	_, exists := s.storage.bookStorage.books[bookID]
	if !exists {
		return ErrBookNotFound
	}

	_, exists = s.storage.readerStorage.readers[readerID]
	if !exists {
		return ErrReaderNotFound
	}

	if bookCopy, existsCopy := s.storage.bookStorage.copies[bookID]; existsCopy {
		if bookCopy.ReaderID != 0 {
			return ErrBookAlreadyBorrowed
		}
		bookCopy.ReaderID = readerID
		return nil
	}

	return ErrBookCopyNotFound
}

func (s *Service) ReturnBook(bookID int, readerID int) error {
	_, exists := s.storage.bookStorage.books[bookID]
	if !exists {
		return ErrBookNotFound
	}

	_, exists = s.storage.readerStorage.readers[readerID]
	if !exists {
		return ErrReaderNotFound
	}

	if bookCopy, existsCopy := s.storage.bookStorage.copies[bookID]; existsCopy {
		if bookCopy.ReaderID != readerID {
			return ErrBookNotBorrowed
		}
		bookCopy.ReaderID = 0
		return nil
	}

	return ErrBookCopyNotFound
}
