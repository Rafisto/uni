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

func (s *Service) CreateBook(book *Book) error {
	return s.storage.bookStorage.CreateBook(book)
}

func (s *Service) DeleteBook(id int) error {
	return s.storage.bookStorage.DeleteBook(id)
}

func (s *Service) AddCopy(bookID int) (int, error) {
	return s.storage.bookStorage.AddCopy(bookID)
}

func (s *Service) DeleteCopy(id int) error {
	return s.storage.bookStorage.DeleteCopy(id)
}

func (s *Service) GetBooks() ([]*Book, error) {
	return s.storage.bookStorage.GetBooks()
}

func (s *Service) GetBook(id int) (*Book, error) {
	return s.storage.bookStorage.GetBook(id)
}

func (s *Service) GetReaders() ([]*Reader, error) {
	return s.storage.readerStorage.GetReaders()
}

func (s *Service) GetReader(id int) (*Reader, error) {
	return s.storage.readerStorage.GetReader(id)
}

func (s *Service) CreateReader(reader *Reader) error {
	return s.storage.readerStorage.CreateReader(reader)
}

func (s *Service) DeleteReader(id int) error {
	return s.storage.readerStorage.DeleteReader(id)
}
