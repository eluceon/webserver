#ifndef HTTP_RESPONSE_HPP
# define HTTP_RESPONSE_HPP

namespace ft {
	class HttpResponse {
		public:
			HttpResponse();
			HttpResponse(const HttpResponse& other);
			~HttpResponse();

			HttpResponse& operator=(const HttpResponse& other);

			enum e_httpStatusCodes {
				/* Information responses */
				CONTINUE						= 100,
				SWITCHING_PROTOCOLS 			= 101,
				PROCESSING						= 102,
				EARLY_HINTS						= 103,
				/* Successful responses */
				OK								= 200,
				CREATED							= 201,
				ACCEPTED						= 202,
				NON_AUTHORITATIVE_INFORMATION	= 203,
				NO_CONTENT						= 204,
				RESET_CONTENT					= 205,
				PARTIAL_CONTENT					= 206,
				/* Redirection messages */
				MULTIPLE_CHOICES				= 300,
				MOVED_PERMANENTLY				= 301,
				FOUND							= 302,
				SEE_OTHER						= 303,
				NOT_MODIFIED					= 304,
				USE_PROXY						= 305,
				// SWITCH_PROXY					= 306,		// No longer used
				TEMPORARY_REDIRECT				= 307,
				PERMANENT_REDIRECT				= 308,
				/* Client error responses */
				BAD_REQUEST						= 400,
				UNAUTHORIZED					= 401,
				PAYMENT_REQUIRED				= 402,
				FORBIDDEN						= 403,
				NOT_FOUND						= 404,
				METHOD_NOT_ALLOWED				= 405,
				NOT_ACCEPTABLE					= 406,
				PROXY_AUTHENTICATION_REQUIRED	= 407,
				REQUEST_TIMEOUT					= 408,
				CONFLICT						= 409,
				GONE							= 410,
				LENGTH_REQUIRED					= 411,
				PRECONDITION_FAILED				= 412,
				PAYLOAD_TOO_LARGE				= 413,
				URI_TOO_LONG					= 414,
				UNSUPPORTED_MEDIA_TYPE			= 415,
				RANGE_NOT_SATISFIABLE			= 416,
				EXPECTATION_FAILED				= 417,
				UPGRADE_REQUIRED				= 426,
				/* Server error responses */
				INTERNAL_SERVER_ERROR			= 500,
				NOT_IMPLEMENTED					= 501,
				BAD_GATEWAY						= 502,
				SERVICE_UNAVAILABLE				= 503,
				GATEWAY_TIMEOUT					= 504,
				HTTP_VERSION_NOT_SUPPORTED		= 505
			};

		private:
	};
	
} // namespace ft


#endif