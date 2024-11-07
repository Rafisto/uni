package main

import (
	"github.com/gin-gonic/gin"

	swaggerFiles "github.com/swaggo/files"
	ginSwagger "github.com/swaggo/gin-swagger"

	_ "rwlodarczyk.pl/library/docs"
)

func populate(s LibraryStorage) {
	// Create readers
	readers := []Reader{
		{Name: "Michał", Surname: "Wiśniewski"},
		{Name: "Till", Surname: "Lindemann"},
		{Name: "Freddie", Surname: "Mercury"},
		{Name: "Eric", Surname: "Clapton"},
		{Name: "David", Surname: "Gilmour"},
	}

	for _, r := range readers {
		err := s.CreateReader(&r)
		if err != nil {
			panic(err)
		}
	}

	// Create classical literature books
	classicalBooks := []Book{
		{Title: "Catch-22", Author: "Joseph Heller"},
		{Title: "Fight Club", Author: "Chuck Palahniuk"},
		{Title: "1984", Author: "George Orwell"},
		{Title: "Brave New World", Author: "Aldous Huxley"},
		{Title: "Memoirs from the house of the dead", Author: "Fyodor Dostoevsky"},
	}

	for _, b := range classicalBooks {
		err := s.CreateBook(&b)
		if err != nil {
			panic(err)
		}
	}

	// Create 3 copies of each book
	for i := 1; i < 6; i++ {
		_, err := s.CreateCopy(i)
		if err != nil {
			panic(err)
		}
		_, err = s.CreateCopy(i)
		if err != nil {
			panic(err)
		}
		_, err = s.CreateCopy(i)
		if err != nil {
			panic(err)
		}
	}
}

// @title           Library API
// @version         1.0
// @description     This is a sample Library API.
// @termsOfService  https://github.com/Rafisto/uni

// @contact.name   API Support
// @contact.url    https://github.com/Rafisto
// @contact.email  rvrelay@gmail.com

// @host      localhost:8080
// @BasePath  /

// @externalDocs.description  OpenAPI
// @externalDocs.url          https://swagger.io/resources/open-api/
func main() {
	storage := NewInMemoryStorage()

	populate(storage)

	server := &HTTPServer{storage: storage}

	router := gin.Default()

	router.GET("/books", server.GetBooksHandler)
	router.GET("/books/:id", server.GetBookHandler)
	router.POST("/books", server.CreateBookHandler)
	router.DELETE("/books/:id", server.DeleteBookHandler)

	router.POST("/books/:id/copies", server.CreateCopyHandler)
	router.GET("/copies", server.GetAllCopiesHandler)
	router.DELETE("/copies/:id", server.DeleteCopyHandler)

	router.POST("/borrow", server.BorrowBookHandler)
	router.POST("/return", server.ReturnBookHandler)

	router.GET("/readers", server.GetReadersHandler)
	router.GET("/readers/:id", server.GetReaderHandler)
	router.POST("/readers", server.CreateReaderHandler)
	router.DELETE("/readers/:id", server.DeleteReaderHandler)

	router.GET("/docs/*any", ginSwagger.WrapHandler(swaggerFiles.Handler))

	res := router.Run(":8080")
	if res != nil {
		panic(res)
	}
}
