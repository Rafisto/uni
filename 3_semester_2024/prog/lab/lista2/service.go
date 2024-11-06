package main

var _ LibraryService = (*Service)(nil)

type Service struct {
	storage *InMemoryStorage
}

func NewService(storage *InMemoryStorage) *Service {
	return &Service{storage: storage}
}

func (s *Service) GetCopiesByReader(readerID int) ([]*FullCopy, error) {
	_, exists := s.storage.readers[readerID]
	if !exists {
		return nil, ErrReaderNotFound
	}

	copies, err := s.storage.GetCopies()
	if err != nil {
		return nil, err
	}

	bookList := make([]*FullCopy, 0)
	for _, copy := range copies {
		if copy.ReaderID == readerID {
			book, err := s.storage.GetBook(copy.BookID)
			if err != nil {
				return nil, err
			}
			bookList = append(bookList, &FullCopy{Book: *book, BookCopy: *copy})
		}
	}

	return bookList, nil
}

func (s *Service) BorrowBook(bookID int, readerID int) error {
	_, exists := s.storage.books[bookID]
	if !exists {
		return ErrBookNotFound
	}

	_, exists = s.storage.readers[readerID]
	if !exists {
		return ErrReaderNotFound
	}

	copies, err := s.storage.GetCopies()
	if err != nil {
		return ErrBookCopyNotFound
	}

	bookCopies := make([]*BookCopy, 0)
	for _, copy := range copies {
		if copy.BookID == bookID {
			bookCopies = append(bookCopies, copy)
		}
	}

	available := 0
	for _, copy := range bookCopies {
		if copy.ReaderID == readerID {
			return ErrBookAlreadyBorrowed
		}
		if copy.ReaderID == 0 {
			available = copy.CopyID
		}
	}

	if available == 0 {
		return ErrBookCopyNotAvaialble
	}

	err = s.storage.UpdateCopy(available, readerID)
	if err != nil {
		return err
	}

	return nil
}

func (s *Service) ReturnBook(copyID int, readerID int) error {
	_, exists := s.storage.copies[copyID]
	if !exists {
		return ErrBookCopyNotFound
	}

	_, exists = s.storage.readers[readerID]
	if !exists {
		return ErrReaderNotFound
	}

	if s.storage.copies[copyID].ReaderID != readerID {
		return ErrBookNotBorrowed
	}

	if s.storage.copies[copyID].ReaderID == 0 {
		return ErrBookNotBorrowed
	}

	err := s.storage.UpdateCopy(copyID, 0)
	if err != nil {
		return err
	}

	return nil
}
