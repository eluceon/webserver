#ifndef HTTP_RESPONSE_HPP
# define HTTP_RESPONSE_HPP

namespace ft {
	class HttpResponse {
		public:
			HttpResponse();
			HttpResponse(const HttpResponse& other);
			~HttpResponse();

			HttpResponse& operator=(const HttpResponse& other);

		protected:
	};
	
} // namespace ft


#endif